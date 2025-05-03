#ifndef __COMMON_TIMER_H__
#define __COMMON_TIMER_H__

#include <thread>
#include <chrono>
#include <functional>
#include <csignal>
#include <atomic>

std::atomic<bool> g_timer_running(true);

class Timer {
public:
    Timer(std::function<void()> callback, int ms) 
        : m_callback(callback), m_interval_ms(ms) {
        m_thread = std::thread(&Timer::Run, this);
        std::signal(SIGINT, [](int signal) {g_timer_running = false;});
    }

    ~Timer() {  if(m_thread.joinable()) m_thread.join(); }
private:
    void Run() {
        auto next_wake_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(m_interval_ms);
        while(g_timer_running) {
            if(std::chrono::steady_clock::now() < next_wake_time) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }

            m_callback(); 
            next_wake_time += std::chrono::milliseconds(m_interval_ms);
        }
    }
protected:
    std::thread m_thread;
    std::function<void()> m_callback;
    int m_interval_ms;
};

#endif // __COMMON_TIMER_H__