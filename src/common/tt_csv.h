#ifndef __COMMON_CSV_H__
#define __COMMON_CSV_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

template<typename T>
class CSVManager {
public:
    static CSVManager<T>* getInstance() {
        if (instance == nullptr) instance = new CSVManager<T>();
        return instance;
    }

    ~CSVManager() {}
    CSVManager(const CSVManager&) = delete;
    CSVManager& operator=(const CSVManager&) = delete;

    std::vector<std::vector<T>> ReadCSV(const std::string& filename) {
        std::vector<std::vector<T>> data;
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::vector<T> row;
            std::stringstream ss(line);
            std::string cell;

            while (std::getline(ss, cell, ',')) {
                T value;
                std::istringstream iss(cell);
                iss >> value;
                row.push_back(value);
            }

            data.push_back(row);
        }

        return data;
    }

    void WriteCSV(const std::vector<std::vector<T>>& data, const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i != row.size() - 1) file << ",";
            }
            file << "\n";
        }
    }
private:
    static CSVManager* instance;
    CSVManager() {}  
};

template<typename T>
CSVManager<T>* CSVManager<T>::instance = nullptr;

#define CSV_READ(type, filename) CSVManager<type>::getInstance()->ReadCSV(filename)
#define CSV_WRITE(type, data, filename) CSVManager<type>::getInstance()->WriteCSV(data, filename)

#endif // __COMMON_CSV_H__