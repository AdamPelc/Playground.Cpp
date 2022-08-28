#include <iostream>
#include "Animal/Dog/Dog.hpp"
#include "Animal/Cat/Cat.hpp"
#include "Serialize/JSON/JsonSerializer.hpp"
#include "Serialize/XML/XmlSerializer.hpp"

int main() {
    std::cout << "Hello World! Adam! \n";

    // Create animals
    Cat cat("Toffee", 4);
    Dog dog("Harry", 8);

    JsonSerializer jsonSerializer;
    std::cout << "Serialize animals using JSON:\n";
    std::cout << cat.Serialize(jsonSerializer) << "\n";
    std::cout << dog.Serialize(jsonSerializer) << "\n";

    XmlSerializer xmlSerializer;
    std::cout << "Serialize animal using XML:\n";
    std::cout << cat.Serialize(xmlSerializer) << "\n";
    std::cout << dog.Serialize(xmlSerializer) << "\n";

    return 0;
}
