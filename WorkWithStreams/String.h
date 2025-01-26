#pragma once
#include "ISerializable.h"

class String : public ISerializable {
private:
    char* str;
    size_t size;

public:
    String();
    String(size_t customSize);
    String(const char* input);
    String(const String& other);
    ~String();

    void input();
    void output() const;
    size_t length() const;

    std::ostream& Serialize(std::ostream& output) override;
    std::istream& Deserialize(std::istream& input) override;
    std::ostream& Serialize(std::string& path) override;
    std::istream& Deserialize(std::string& path) override;
    std::ostream& Serialize() override;
    std::istream& Deserialize() override;
};