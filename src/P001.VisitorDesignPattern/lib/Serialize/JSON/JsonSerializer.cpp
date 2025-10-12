#include "JsonSerializer.hpp"

#include "Animal/Cat/Cat.hpp"
#include "Animal/Dog/Dog.hpp"
#include "Animal/Parrot/Parrot.hpp"

std::string JsonSerializer::Serialize( const Cat& cat ) const {
    using namespace std::string_literals;

    std::string response;
    response += "{\n";
    response += "\t\"species\": \"Cat\",\n";
    response += "\t\"name\": " + cat.GetName() + ",\n";
    response += "\t\"age\": " + std::to_string(cat.GetAge()) + ",\n";
    response += "}";

    return response;
}

std::string JsonSerializer::Serialize( const Dog& dog ) const {
    using namespace std::string_literals;

    std::string response;
    response += "{\n";
    response += "\t\"species\": \"Dog\",\n";
    response += "\t\"name\": " + dog.GetName() + ",\n";
    response += "\t\"age\": " + std::to_string(dog.GetAge()) + ",\n";
    response += "}";

    return response;
}

std::string JsonSerializer::Serialize( const Parrot& parrot ) const {
    std::string response;
    response += "{\n";
    response += "\t\"species\": \"Parrot\",\n";
    response += "\t\"name\": " + parrot.GetName() + ",\n";
    response += "\t\"age\": " + std::to_string(parrot.GetAge()) + ",\n";
    response += "}";

    return response;
}
