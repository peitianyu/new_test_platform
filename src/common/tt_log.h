#ifndef __COMMON_LOG_H__
#define __COMMON_LOG_H__

#include <iostream>

template <typename... Args, typename O>
O & print_base(O &out, Args&&... args) {
    auto a = {(out << std::forward<Args>(args), 0)...};
    (void)a;
    return out;
} 

#define TT_PRINT_RED       "\033[31m"
#define TT_PRINT_YELLOW    "\033[33m"
#define TT_PRINT_GREEN     "\033[32m"
#define TT_PRINT_BLUE      "\033[34m"
#define TT_PRINT_WHITE     "\033[37m"
#define TT_PRINT_GRAY      "\033[90m"
#define TT_PRINT_CYAN      "\033[36m"
#define TT_PRINT_PURPLE    "\033[35m"
#define TT_PRINT_NONE      "\033[0m"

#define LOG(...) print_base(std::cout, __VA_ARGS__, TT_PRINT_NONE) << std::endl;
#define LOG_INFO(...) LOG(TT_PRINT_GREEN, __VA_ARGS__);
#define LOG_WARN(...) LOG(TT_PRINT_YELLOW, __VA_ARGS__);
#define LOG_ERROR(...) LOG(TT_PRINT_RED, __VA_ARGS__);

#endif // __COMMON_LOG_H__