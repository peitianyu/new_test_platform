#ifndef __INI_PARSE_H__
#define __INI_PARSE_H__

#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<sys/stat.h>
#include "tt_log.h"


class IniParse
{
public:
    struct Param {
        char comment;
        char separator;
        Param(char c = ';', char s = '=') : comment(c), separator(s) {}
    };

    IniParse(const std::string& filename, const Param& p = Param())
        :m_param(p), m_filename(filename), m_curr_section("") {}

    bool UpdateParam() {
        if(!HasFileChanged()) return false;

        m_ifs.open(m_filename);
        if(!m_ifs.is_open()) {
            LOG("OPEN INI FILE FAILED: ", m_filename);
            return false;
        }

        std::string line;
        while(std::getline(m_ifs, line)) {
            Trim(line);
            if(line.empty() || line[0] == m_param.comment)
                continue;

            if(line[0] == '[') {
                if(line.back() == ']')  m_curr_section = line.substr(1, line.length() - 2);
                else                    LOG("INCALID SECTION FORMET: ", line);
            }
            else if(!m_curr_section.empty()) {
                size_t separator_pos = line.find(m_param.separator);
                if(separator_pos != std::string::npos) {
                    std::string key = line.substr(0, separator_pos);
                    std::string value = line.substr(separator_pos + 1);
                    Trim(key);
                    Trim(value);
                    m_map[m_curr_section][key] = value;
                }
            }
        }
        m_ifs.close();

        return true;
    }

    template<typename DataType>
    bool GetValue(const std::string& section, const std::string& key, DataType& value) {
        auto section_it = m_map.find(section);
        if (section_it == m_map.end()) return false;

        auto& section_map = section_it->second;
        auto key_it = section_map.find(key);
        if (key_it == section_map.end()) return false;

        std::istringstream iss(key_it->second);
        if (std::is_same<DataType, bool>::value) {
            std::string bool_str;
            iss >> bool_str;
            if (bool_str == "true") {
                value = true;
                return true;
            } else if (bool_str == "false") {
                value = false;
                return true;
            } else {
                return false;
            }
        } else {
            if ((iss >> value).fail()) return false;
            return true;
        }
    }

    template<typename DataType>
    bool GetVectorValue(const std::string& section, const std::string& key, std::vector<DataType>& value) {
        auto section_it = m_map.find(section);
        if(section_it == m_map.end()) return false;

        auto& section_map = section_it->second;
        auto key_it = section_map.find(key);
        if(key_it == section_map.end()) return false;
        value.clear();

        std::string str = key_it->second;
        str.erase(std::remove(str.begin(), str.end(), '{'), str.end());
        str.erase(std::remove(str.begin(), str.end(), '}'), str.end());
        std::istringstream iss(str);
        std::string val;
        while (std::getline(iss, val, ',')) {
            std::istringstream iss(val);
            DataType data;
            if((iss >> data).fail()) return false;
            value.push_back(data);
        }
        return true;
    }

    template<typename DataType>
    void SetValue(const std::string& section, const std::string& key, const DataType& value) {
        if constexpr (std::is_convertible_v<DataType, std::string_view>)
            m_map[section][key] = std::string(value);
        else                                                
            m_map[section][key] = std::to_string(value);
    }

    template<typename DataType>
    void SetValue(const std::string& section, const std::string& key, const std::vector<DataType>& value) {
        std::string str = "{";
        bool first = true; 

        for (auto& v : value) {
            if (!first) str += ",";
            str += std::to_string(v);
            first = false;
        }

        str += "}";
        m_map[section][key] = str;
    }

    void UpdateIni() {
        std::ofstream ofs;
        ofs.open(m_filename, std::ios::out);
        if(!ofs.is_open()) {
            LOG("OPEN INI FILE FAILED: ", m_filename);
            return;
        }
        for(auto& section : m_map) {
            ofs << "[" << section.first << "]" << std::endl;
            for(auto& item : section.second) 
                ofs << item.first << m_param.separator << item.second << std::endl;
            ofs << std::endl;
        }
        ofs.close();
    }

    const std::map<std::string, std::map<std::string, std::string>>& GetData() const { return m_map; }
private:
    void Trim(std::string& str) {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        str = (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
    }
    
    bool HasFileChanged() {
        static time_t last_modified;
        struct stat file_status;
        if (stat(m_filename.c_str(), &file_status) == -1) {
            LOG("ERROR ACCESSING FAILED: ", m_filename);
            return false;
        }
        if (file_status.st_mtime != last_modified) {
            last_modified = file_status.st_mtime;
            return true;
        }
        return false;
    }
private:
    Param m_param;
    std::string m_filename;
    std::ifstream m_ifs;
    std::string m_curr_section;
    std::map<std::string, std::map<std::string, std::string>> m_map; // key: section, value: key-value pairs
};

#endif // __INI_PARSE_H__