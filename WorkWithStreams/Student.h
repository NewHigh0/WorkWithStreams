#pragma once
#include <string>
#include <fstream>
#include "ISerializable.h"

class Student : public ISerializable {
private:
    std::string fullName;
    std::string group;
    int age;

public:
    Student() : fullName(""), group(""), age(0) {}

    Student(const std::string& name, const std::string& gr, int a, double score)
        : fullName(name), group(gr), age(a) {}

    void input() {
        std::cout << "Enter student full name: ";
        std::getline(std::cin, fullName);
        std::cout << "Enter student group: ";
        std::getline(std::cin, group);
        std::cout << "Enter student age: ";
        std::cin >> age;
        std::cin.ignore();
    }

    void output() const {
        std::cout << "Full Name: " << fullName << std::endl;
        std::cout << "Group: " << group << std::endl;
        std::cout << "Age: " << age << std::endl;
    }

    std::ostream& Serialize(std::ostream& output) override {
        size_t nameSize = fullName.length();
        size_t groupSize = group.length();

        output.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        output.write(fullName.c_str(), nameSize);

        output.write(reinterpret_cast<char*>(&groupSize), sizeof(groupSize));
        output.write(group.c_str(), groupSize);

        output.write(reinterpret_cast<const char*>(&age), sizeof(age));

        return output;
    }

    std::istream& Deserialize(std::istream& input) override {
        size_t nameSize, groupSize;

        input.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        fullName.resize(nameSize);
        input.read(&fullName[0], nameSize);

        input.read(reinterpret_cast<char*>(&groupSize), sizeof(groupSize));
        group.resize(groupSize);
        input.read(&group[0], groupSize);

        input.read(reinterpret_cast<char*>(&age), sizeof(age));

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
        std::string defaultPath = "student_serialization.bin";
        return Serialize(defaultPath);
    }

    std::istream& Deserialize() override {
        std::string defaultPath = "student_serialization.bin";
        return Deserialize(defaultPath);
    }
};