#include "Animal/Cat/Cat.hpp"
#include "Animal/Dog/Dog.hpp"
#include "Animal/Parrot/Parrot.hpp"
#include "Serialize/JSON/JsonSerializer.hpp"
#include "Serialize/XML/XmlSerializer.hpp"

#include <iostream>

int main() {
    std::cout << "Hello World! Adam! \n";

    // Create animals
    Cat cat("Toffee", 4);
    Dog dog("Harry", 8);
    Parrot parrot("Arrr", 99);

    JsonSerializer jsonSerializer;
    std::cout << "Serialize animals using JSON:\n";
    std::cout << cat.Serialize(jsonSerializer) << "\n";
    std::cout << dog.Serialize(jsonSerializer) << "\n";
    std::cout << parrot.Serialize(jsonSerializer) << "\n";

    XmlSerializer xmlSerializer;
    std::cout << "Serialize animal using XML:\n";
    std::cout << cat.Serialize(xmlSerializer) << "\n";
    std::cout << dog.Serialize(xmlSerializer) << "\n";
    std::cout << parrot.Serialize(xmlSerializer) << "\n";

    return 0;
}
