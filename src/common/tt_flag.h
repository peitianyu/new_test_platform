#ifndef __COMMON_FLAG_H__
#define __COMMON_FLAG_H__

#include <iostream>
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <stdexcept>
#include <sstream>

class FlagManager {
public:
    static FlagManager& GetInstance() {
        static FlagManager instance;
        return instance;
    }

    void SetFlags(int argc, char** argv) {
        m_argc = argc;
        m_argv = argv;
    }

    template <typename T>
    T GetFlagValue(const std::string& flag_name) {
        static bool s_update_flag = false;
        if (!s_update_flag) {
            ParseFlags();
            s_update_flag = true;
        }
        
        auto it = m_flag_map.find(flag_name);
        if (it == m_flag_map.end()) throw std::runtime_error("Flag " + flag_name + " not found");
        return Convert<T>(it->second.value);
    }

    template <typename T>
    void DefineFlag(const std::string& name, const std::string& default_value, const std::string& description) {
        Flag flag(name, default_value, description, typeid(T));
        m_flag_map.emplace(name, flag);
    }

    void PrintFlags() {
        for (const auto& pair : m_flag_map) std::cout << "--" << pair.first << ": " << pair.second.value << " (" << pair.second.description << ")" << std::endl;
    }
private:
    FlagManager() = default;
    FlagManager(const FlagManager&) = delete;
    FlagManager& operator=(const FlagManager&) = delete;

    void ParseFlags() {
        for (int i = 1; i < m_argc; ++i) {
            if (m_argv[i][0] == '-' && m_argv[i][1] == '-') {
                std::string arg = m_argv[i];
                size_t equal_pos = arg.find('=');
                std::string flag_name = arg.substr(2, equal_pos != std::string::npos ? equal_pos - 2 : arg.size() - 1);
                std::string flag_value;
                if(equal_pos != std::string::npos) flag_value = arg.substr(equal_pos + 1);
                else if(++i < m_argc)              flag_value = m_argv[i];
                
                auto it = m_flag_map.find(flag_name);
                if(it != m_flag_map.end()) it->second.value = flag_value;
            }
        }
    }

    template <typename T>
    T Convert(const std::string& value) {
        std::istringstream iss(value);
        T result;
        iss >> result;
        return result;
    }

    struct Flag {
        std::string name;
        std::string value;
        std::string description;
        std::type_index type;

        Flag(const std::string& name, const std::string& value, const std::string& description, std::type_index type)
            : name(name), value(value), description(description), type(type) {}
    };

    int m_argc;
    char** m_argv;
    std::map<std::string, Flag> m_flag_map;
};

#define PARSE_FLAG(argc, argv) FlagManager::GetInstance().SetFlags(argc, argv)
#define DEFINE_FLAG(type, name, default_value, description) FlagManager::GetInstance().DefineFlag<type>(#name, #default_value, description)
#define GET_FLAG(name, type) FlagManager::GetInstance().GetFlagValue<type>(#name)
#define PRINT_FLAGS()                                       FlagManager::GetInstance().PrintFlags()

#endif