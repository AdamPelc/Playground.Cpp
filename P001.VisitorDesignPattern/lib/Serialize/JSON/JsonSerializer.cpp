#include "JsonSerializer.hpp"

#include "Animal/Cat/Cat.hpp"
#include "Animal/Dog/Dog.hpp"
#include "Animal/Parrot/Parrot.hpp"

std::string JsonSerializer::SerializeCat( const Cat& cat ) {
    using namespace std::string_literals;

    std::string response;
    response += "{\n";
    response += "\t\"species\": \"Cat\",\n";
    response += "\t\"name\": " + cat.GetName() + ",\n";
    response += "\t\"age\": " + std::to_string(cat.GetAge()) + ",\n";
    response += "}";

    return response;
}

std::string JsonSerializer::SerializeDog( const Dog& dog ) {
    using namespace std::string_literals;

    std::string response;
    response += "{\n";
    response += "\t\"species\": \"Dog\",\n";
    response += "\t\"name\": " + dog.GetName() + ",\n";
    response += "\t\"age\": " + std::to_string(dog.GetAge()) + ",\n";
    response += "}";

    return response;
}

std::string JsonSerializer::SerializeParrot( const Parrot& parrot ) {
    std::string response;
    response += "{\n";
    response += "\t\"species\": \"Parrot\",\n";
    response += "\t\"name\": " + parrot.GetName() + ",\n";
    response += "\t\"age\": " + std::to_string(parrot.GetAge()) + ",\n";
    response += "}";

    return response;
}
