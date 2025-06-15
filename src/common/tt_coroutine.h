#ifndef STDEX_COROUTINE_H_
#define STDEX_COROUTINE_H_

#ifndef STACK_LIMIT
#define STACK_LIMIT (1024 * 1024)
#endif

#include <cassert>
#include <vector>
#include <list>
#include <thread>
#include <future>
#include <ucontext.h>

namespace coroutine {
    typedef unsigned routine_t;

    struct Routine {
        std::function<void()> func;
        char *stack;
        bool finished;
        ucontext_t ctx;

        Routine(std::function<void()> f) : func(std::move(f)), stack(nullptr), finished(false) {}
        ~Routine() { delete[] stack; }
    };

    struct Ordinator {
        std::vector<Routine*> routines;
        std::list<routine_t> indexes;
        routine_t current = 0;
        size_t stack_size;
        ucontext_t ctx;

        Ordinator(size_t ss = STACK_LIMIT) : stack_size(ss) {}
        ~Ordinator() { for (auto &routine : routines) delete routine; }
    };

    thread_local static Ordinator ordinator;

    inline routine_t create(std::function<void()> f) {
        Routine *routine = new Routine(std::move(f));

        if (ordinator.indexes.empty()) {
            ordinator.routines.push_back(routine);
            return ordinator.routines.size();
        } else {
            routine_t id = ordinator.indexes.front();
            ordinator.indexes.pop_front();
            assert(ordinator.routines[id - 1] == nullptr);
            ordinator.routines[id - 1] = routine;
            return id;
        }
    }

    inline void destroy(routine_t id) {
        Routine *routine = ordinator.routines[id - 1];
        assert(routine != nullptr);
        delete routine;
        ordinator.routines[id - 1] = nullptr;
    }

    inline void entry() {
        routine_t id = ordinator.current;
        Routine *routine = ordinator.routines[id - 1];
        routine->func();
        routine->finished = true;
        ordinator.current = 0;
        ordinator.indexes.push_back(id);
    }

    inline int resume(routine_t id) {
        assert(ordinator.current == 0);

        Routine *routine = ordinator.routines[id - 1];
        if (!routine) return -1;
        if (routine->finished) return -2;

        if (!routine->stack) {
            getcontext(&routine->ctx);
            routine->stack = new char[ordinator.stack_size];
            routine->ctx.uc_stack.ss_sp = routine->stack;
            routine->ctx.uc_stack.ss_size = ordinator.stack_size;
            routine->ctx.uc_link = &ordinator.ctx;
            ordinator.current = id;
            makecontext(&routine->ctx, reinterpret_cast<void (*)(void)>(entry), 0);
        }
        ordinator.current = id;
        swapcontext(&ordinator.ctx, &routine->ctx);
        return 0;
    }

    inline void yield() {
        routine_t id = ordinator.current;
        Routine *routine = ordinator.routines[id - 1];
        assert(routine != nullptr);
        ordinator.current = 0;
        swapcontext(&routine->ctx, &ordinator.ctx);
    }

    inline routine_t current() { return ordinator.current; }

    template <typename Function>
    inline auto await(Function &&func) -> decltype(func()) {
        auto future = std::async(std::launch::async, std::forward<Function>(func));
        std::future_status status = future.wait_for(std::chrono::milliseconds(0));

        while (status == std::future_status::timeout) {
            if (ordinator.current != 0) yield();
            status = future.wait_for(std::chrono::milliseconds(0));
        }
        return future.get();
    }

    template <typename Function, typename... Args>
    inline auto await(Function &&func, Args &&...args) -> decltype(func(std::forward<Args>(args)...)) {
        using ResultType = decltype(func(std::forward<Args>(args)...));
        std::future<ResultType> future = std::async(
            std::launch::async,
            std::forward<Function>(func),
            std::forward<Args>(args)...);

        std::future_status status = future.wait_for(std::chrono::milliseconds(0));

        while (status == std::future_status::timeout) {
            if (ordinator.current != 0) yield();
            status = future.wait_for(std::chrono::milliseconds(0));
        }
        return future.get();
    }

    template <typename Type>
    class Channel {
    public:
        Channel() : _taker(0) {}
        Channel(routine_t id) : _taker(id) {}

        inline void consumer(routine_t id) { _taker = id; }

        inline void push(const Type &obj) {
            _list.push_back(obj);
            if (_taker && _taker != current()) resume(_taker);
        }

        inline void push(Type &&obj) {
            _list.push_back(std::move(obj));
            if (_taker && _taker != current()) resume(_taker);
        }

        inline Type pop() {
            if (!_taker) _taker = current();
            while (_list.empty()) yield();

            Type obj = std::move(_list.front());
            _list.pop_front();
            return std::move(obj);
        }

        inline Type front() {
            if (!_taker) _taker = current();
            while (_list.empty()) yield();

            return _list.front();
        }

        inline void clear() { _list.clear(); }
        inline void touch() { if (_taker && _taker != current()) resume(_taker); }
        inline size_t size() { return _list.size(); }
        inline bool empty() { return _list.empty(); }

    private:
        std::list<Type> _list;
        routine_t _taker;
    };
}

#endif // STDEX_COROUTINE_H_