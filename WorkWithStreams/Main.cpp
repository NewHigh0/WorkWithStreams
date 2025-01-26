#include <iostream>
#include "String.h"

int main() {
    
    String s1("Hello, World!");
    String s2;

    std::string filePath = "test_serialization.bin";
    s1.Serialize(filePath);

    s2.Deserialize(filePath);

    std::cout << "Original string: ";
    s1.output();
    std::cout << "Deserialized string: ";
    s2.output();

    return 0;
}