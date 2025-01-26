#include <iostream>
#include "String.h"
#include "Contacts.h"

int main() {
    
    /*String s1("Hello, World!");
    String s2;

    std::string filePath = "test_serialization.bin";
    s1.Serialize(filePath);

    s2.Deserialize(filePath);

    std::cout << "Original string: ";
    s1.output();
    std::cout << "Deserialized string: ";
    s2.output();*/

    Contacts contact1("John", "+1234567890", "john@gmail.com");

    std::cout << "Original Contact:" << std::endl;
    contact1.output();

    std::string filePath = "contact_test.bin";
    contact1.Serialize(filePath);

    Contacts contact2;

    contact2.Deserialize(filePath);

    std::cout << "\nDeserialized Contact:" << std::endl;
    contact2.output();

    return 0;
}