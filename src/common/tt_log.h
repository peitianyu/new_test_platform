#ifndef __COMMON_LOG_H__
#define __COMMON_LOG_H__

#include <iostream>

template <typename... Args, typename O>
O & print_base(O &out, Args&&... args) {
    auto a = {(out << std::forward<Args>(args), 0)...};
    (void)a;
    return out;
} 

#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
[[maybe_unused]]
static std::string get_curr_time_str() {
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t);
    auto now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
    std::ostringstream oss;
    oss << "[" << std::put_time(&now_tm, "%Y-%m-%d %H-%M-%S") << ":" << std::setw(6) << std::setfill('0') << now_us.count() << "]";
    return oss.str();
} 

#define LOG(...) print_base(std::cout, __VA_ARGS__) << std::endl;
#define LOG_INFO(...) LOG(get_curr_time_str(), " [INFO] ", __VA_ARGS__);
#define LOG_WARN(...) LOG(get_curr_time_str(), " [WARN] ", __VA_ARGS__);
#define LOG_ERROR(...) LOG(get_curr_time_str(), " [ERRO] ", __VA_ARGS__);

#endif // __COMMON_LOG_H__