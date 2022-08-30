#include "Animal/Cat/Cat.hpp"
#include "Animal/Dog/Dog.hpp"
#include "Animal/Parrot/Parrot.hpp"
#include "Serialize/JSON/JsonSerializer.hpp"
#include "Serialize/XML/XmlSerializer.hpp"

#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::cout << "Hello World! Adam! \n";

    // Create serializable animals
    std::vector<std::unique_ptr<ISerializable>> serializable_animals;
    serializable_animals.emplace_back( std::make_unique<Cat>( "Toffee", 4 ) );
    serializable_animals.emplace_back( std::make_unique<Dog>( "Harry", 8 ) );
    serializable_animals.emplace_back( std::make_unique<Parrot>( "Arrr", 99 ) );

    std::unique_ptr<Serializer> serializer = std::make_unique<JsonSerializer>();
    std::cout << "\nSerialize animals using JSON:\n";
    for ( const auto& animal : serializable_animals ) {
        std::cout << animal->Serialize( *serializer ) << "\n";
    }

    serializer = std::make_unique<XmlSerializer>();
    std::cout << "\nSerialize animal using XML:\n";
    for ( const auto& animal : serializable_animals ) {
        std::cout << animal->Serialize( *serializer ) << "\n";
    }

    return 0;
}
