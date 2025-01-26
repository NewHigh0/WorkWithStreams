#pragma once
#include <string>
#include <fstream>
#include "ISerializable.h"

class College : public ISerializable {
private:
    std::string name;
    std::string address;
    int foundationYear;
    int studentsCount;

public:
    College() : name(""), address(""), foundationYear(0), studentsCount(0) {}

    College(const std::string& n, const std::string& addr, int year, int students)
        : name(n), address(addr), foundationYear(year), studentsCount(students) {}

    void output() const {
        std::cout << "College Name: " << name << std::endl;
        std::cout << "Address: " << address << std::endl;
        std::cout << "Foundation Year: " << foundationYear << std::endl;
        std::cout << "Students Count: " << studentsCount << std::endl;
    }

    std::ostream& Serialize(std::ostream& output) override {
        size_t nameSize = name.length();
        size_t addressSize = address.length();

        output.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        output.write(name.c_str(), nameSize);

        output.write(reinterpret_cast<char*>(&addressSize), sizeof(addressSize));
        output.write(address.c_str(), addressSize);

        output.write(reinterpret_cast<const char*>(&foundationYear), sizeof(foundationYear));
        output.write(reinterpret_cast<const char*>(&studentsCount), sizeof(studentsCount));

        return output;
    }

    std::istream& Deserialize(std::istream& input) override {
        size_t nameSize, addressSize;

        input.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        name.resize(nameSize);
        input.read(&name[0], nameSize);

        input.read(reinterpret_cast<char*>(&addressSize), sizeof(addressSize));
        address.resize(addressSize);
        input.read(&address[0], addressSize);

        input.read(reinterpret_cast<char*>(&foundationYear), sizeof(foundationYear));
        input.read(reinterpret_cast<char*>(&studentsCount), sizeof(studentsCount));

        return input;
    }

    std::ostream& Serialize(std::string& path) override {
        std::ofstream file(path, std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file for serialization" << std::endl;
            return file;
        }
        return Serialize(file);
    }

    std::istream& Deserialize(std::string& path) override {
        std::ifstream file(path, std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file for deserialization" << std::endl;
            return file;
        }
        return Deserialize(file);
    }

    std::ostream& Serialize() override {
        std::string defaultPath = "college_serialization.bin";
        return Serialize(defaultPath);
    }

    std::istream& Deserialize() override {
        std::string defaultPath = "college_serialization.bin";
        return Deserialize(defaultPath);
    }
};