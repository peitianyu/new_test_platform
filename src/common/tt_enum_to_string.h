#ifndef __ENUM_TO_STRING_H__
#define __ENUM_TO_STRING_H__

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#define MAKE_ENUM(name, ...)                                                                \
    enum class name { __VA_ARGS__ };                                                        \
    static const auto& Enum_##name##_str_vec = []() {                                       \
        std::istringstream iss(#__VA_ARGS__);                                               \
        std::vector<std::string> vec;                                                       \
        std::string item;                                                                   \
        while (std::getline(iss, item, ',')) {                                              \
            item.erase(std::remove_if(item.begin(), item.end(), ::isspace), item.end());    \
            vec.emplace_back(std::move(item)); }                                            \
        return vec; }();                                                                    \
    static std::string enum_to_string(name val) { return Enum_##name##_str_vec[static_cast<size_t>(val)]; }

#endif // __ENUM_TO_STRING_H__