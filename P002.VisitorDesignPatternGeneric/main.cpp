#include "Animal/Animals/Cat/Cat.hpp"
#include "Animal/Animals/Dog/Dog.hpp"
#include "Animal/Animals/Parrot/Parrot.hpp"
#include "Serialize/JSON/JsonSerializer.hpp"
#include "Serialize/XML/XmlSerializer.hpp"

#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::cout << "Hello World! Adam! \n";

    // Create serializable animals
    std::vector<std::unique_ptr<IVisitableAnimal>> visitableAnimals;
    visitableAnimals.emplace_back( std::make_unique<Cat>( "Toffee", 4 ) );
    visitableAnimals.emplace_back( std::make_unique<Dog>( "Harry", 8 ) );
    visitableAnimals.emplace_back( std::make_unique<Parrot>( "Arrr", 99 ) );

    std::unique_ptr<Serializer> serializer = std::make_unique<JsonSerializer>();
    std::cout << "\nSerialize animals using JSON:\n";
    for ( const auto& animal : visitableAnimals ) {
        animal->Accept( *serializer );
        std::cout << serializer->Serialize() << "\n";
    }

    serializer = std::make_unique<XmlSerializer>();
    std::cout << "\nSerialize animal using XML:\n";
    for ( const auto& animal : visitableAnimals ) {
        animal->Accept( *serializer );
        std::cout << serializer->Serialize() << "\n";
    }

    return 0;
}
