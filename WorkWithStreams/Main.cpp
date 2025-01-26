#include <iostream>
#include "String.h"
#include "Contacts.h"
#include "College.h"

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

    /*Contacts contact1("John", "+1234567890", "john@gmail.com");

    std::cout << "Original Contact:" << std::endl;
    contact1.output();

    std::string filePath = "contact_test.bin";
    contact1.Serialize(filePath);

    Contacts contact2;

    contact2.Deserialize(filePath);

    std::cout << "\nDeserialized Contact:" << std::endl;
    contact2.output();*/

    College college1("Base college", "Random street", 1995, 1200);

    std::cout << "Original College:" << std::endl;
    college1.output();

    std::string filePath = "college_test.bin";
    college1.Serialize(filePath);

    College college2;

    college2.Deserialize(filePath);

    std::cout << "\nDeserialized College:" << std::endl;
    college2.output();

    return 0;
}