#pragma once
#include <string>
#include <fstream>
#include "ISerializable.h"

class Contacts : public ISerializable {
private:
    std::string name;
    std::string phone;
    std::string email;

public:
    Contacts() : name(""), phone(""), email("") {}

    Contacts(const std::string& n, const std::string& p, const std::string& e)
        : name(n), phone(p), email(e) {}

    void output() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Phone: " << phone << std::endl;
        std::cout << "Email: " << email << std::endl;
    }

    std::ostream& Serialize(std::ostream& output) override {
        size_t nameSize = name.length();
        size_t phoneSize = phone.length();
        size_t emailSize = email.length();

        output.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        output.write(name.c_str(), nameSize);

        output.write(reinterpret_cast<char*>(&phoneSize), sizeof(phoneSize));
        output.write(phone.c_str(), phoneSize);

        output.write(reinterpret_cast<char*>(&emailSize), sizeof(emailSize));
        output.write(email.c_str(), emailSize);

        return output;
    }

    std::istream& Deserialize(std::istream& input) override {
        size_t nameSize, phoneSize, emailSize;

        input.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        name.resize(nameSize);
        input.read(&name[0], nameSize);

        input.read(reinterpret_cast<char*>(&phoneSize), sizeof(phoneSize));
        phone.resize(phoneSize);
        input.read(&phone[0], phoneSize);

        input.read(reinterpret_cast<char*>(&emailSize), sizeof(emailSize));
        email.resize(emailSize);
        input.read(&email[0], emailSize);

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
        std::string defaultPath = "contacts_serialization.bin";
        return Serialize(defaultPath);
    }

    std::istream& Deserialize() override {
        std::string defaultPath = "contacts_serialization.bin";
        return Deserialize(defaultPath);
    }
};