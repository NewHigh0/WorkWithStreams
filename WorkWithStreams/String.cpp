#include "String.h"
#include <fstream>

String::String() : String(80) {}

String::String(size_t customSize) : size(customSize + 1) {
    str = new char[size];
    str[0] = '\0';
}

String::String(const char* input) : size(strlen(input) + 1) {
    str = new char[size];
    strcpy_s(str, size, input);
}

String::String(const String& other) : size(other.size) {
    str = new char[size];
    strcpy_s(str, size, other.str);
}

String::~String() {
    delete[] str;
}

void String::input() {
    std::cout << "Enter a String: ";
    std::cin.getline(str, size);
}

void String::output() const {
    std::cout << "String: " << str << std::endl;
}

size_t String::length() const {
    return strlen(str);
}

std::ostream& String::Serialize(std::ostream& output) {
    size_t len = length();
    output.write(reinterpret_cast<char*>(&len), sizeof(len));
    output.write(str, len);
    return output;
}

std::istream& String::Deserialize(std::istream& input) {
    size_t len;
    input.read(reinterpret_cast<char*>(&len), sizeof(len));

    delete[] str;
    size = len + 1;
    str = new char[size];

    input.read(str, len);
    str[len] = '\0';

    return input;
}

std::ostream& String::Serialize(std::string& path) {
    std::ofstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for serialization" << std::endl;
        return file;
    }

    return Serialize(file);
}

std::istream& String::Deserialize(std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for deserialization" << std::endl;
        return file;
    }

    return Deserialize(file);
}

std::ostream& String::Serialize() {
    std::string defaultPath = "default_string_serialization.bin";
    return Serialize(defaultPath);
}

std::istream& String::Deserialize() {
    std::string defaultPath = "default_string_serialization.bin";
    return Deserialize(defaultPath);
}