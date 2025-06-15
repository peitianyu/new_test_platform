#ifndef __COMMON_SERIALIZE_H__
#define __COMMON_SERIALIZE_H__

#include <sstream>
#include <string>
#include <vector>

template <typename T>
void Serialize(const T& data, std::string& out) {
    std::ostringstream oss(std::ios::binary | std::ios::out);
    oss.write(reinterpret_cast<const char*>(&data), sizeof(T));
    out.append(oss.str());
}

template <>
void Serialize<std::string>(const std::string& data, std::string& out) {
    std::ostringstream oss(std::ios::binary | std::ios::out);
    size_t size = data.size();
    oss.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    out.append(oss.str());
    out.append(data);
}

template <typename T>
void SerializeVector(const std::vector<T>& data, std::string& out) {
    size_t size = data.size();
    Serialize(size, out);
    for (const auto& item : data) Serialize(item, out);
}

template <typename T>
void SerializeVectorVector(const std::vector<std::vector<T>>& data, std::string& out) {
    size_t size = data.size();
    Serialize(size, out);
    for (const auto& vec : data) 
        SerializeVector(vec, out);
}

template <typename T>
bool Deserialize(T& data, std::string& in) {
    if (in.size() < sizeof(T)) return false;
    std::istringstream iss(in.substr(0, sizeof(T)), std::ios::binary | std::ios::in);
    iss.read(reinterpret_cast<char*>(&data), sizeof(T));
    in.erase(0, sizeof(T));
    return true;
}

template<>
bool Deserialize<std::string>(std::string& data, std::string& in) {
    size_t size;
    if (in.size() < sizeof(size_t)) return false;
    std::istringstream iss(in.substr(0, sizeof(size_t)), std::ios::binary | std::ios::in);
    iss.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    in.erase(0, sizeof(size_t));

    if (in.size() < size) return false;
    data = in.substr(0, size);
    in.erase(0, size);

    return true;
}

template <typename T>
bool DeserializeVector(std::vector<T>& data, std::string& in) {
    size_t size;
    if (!Deserialize(size, in)) return false;
    data.resize(size);
    for (size_t i = 0; i < size; ++i) {
        if (!Deserialize(data[i], in)) return false;
    }
    return true;
}

template <typename T>
bool DeserializeVectorVector(std::vector<std::vector<T>>& data, std::string& in) {
    size_t size;
    if (!Deserialize(size, in)) return false;
    data.resize(size);
    for (size_t i = 0; i < size; ++i) {
        if (!DeserializeVector(data[i], in)) return false;
    }
    return true;
}

#endif // __COMMON_SERIALIZE_H__