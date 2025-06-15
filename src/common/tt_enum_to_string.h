#ifndef __ENUM_TO_STRING_H__
#define __ENUM_TO_STRING_H__

#include <string>
#include <vector>
#include <sstream>

#define MAKE_ENUM(name, ...) enum class name { __VA_ARGS__}; \
static std::vector<std::string> Enum_##name##_init(){\
    const std::string content = #__VA_ARGS__; \
    std::vector<std::string> str;\
    size_t len = content.length();\
    std::ostringstream temp;\
    for(size_t i = 0; i < len; i ++) {\
    if(isspace(content[i])) continue;\
    else if(content[i] == ',') {\
    str.push_back(temp.str());\
    temp.str(std::string());}\
    else temp<< content[i];}\
    str.push_back(temp.str());\
    return str;}\
static const std::vector<std::string> Enum_##name##_str_vec = Enum_##name##_init();\
static  __attribute__((unused)) std::string enum_to_string(name val){\
    return Enum_##name##_str_vec[static_cast<size_t>(val)];\
}

#endif // __ENUM_TO_STRING_H__