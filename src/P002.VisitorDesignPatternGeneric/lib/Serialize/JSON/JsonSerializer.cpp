#include "JsonSerializer.hpp"

#include "Animal/Animals/Cat/Cat.hpp"
#include "Animal/Animals/Dog/Dog.hpp"
#include "Animal/Animals/Parrot/Parrot.hpp"

void JsonSerializer::Visit(const Cat& cat) {
    using namespace std::string_literals;

    buffer.clear();
    buffer += "{\n";
    buffer += "\t\"species\": \"Cat\",\n";
    buffer += "\t\"name\": " + cat.GetName() + ",\n";
    buffer += "\t\"age\": " + std::to_string(cat.GetAge()) + ",\n";
    buffer += "}";
}

void JsonSerializer::Visit(const Dog& dog) {
    using namespace std::string_literals;

    buffer.clear();
    buffer += "{\n";
    buffer += "\t\"species\": \"Dog\",\n";
    buffer += "\t\"name\": " + dog.GetName() + ",\n";
    buffer += "\t\"age\": " + std::to_string(dog.GetAge()) + ",\n";
    buffer += "}";
}

void JsonSerializer::Visit(const Parrot& parrot) {
    buffer.clear();
    buffer += "{\n";
    buffer += "\t\"species\": \"Parrot\",\n";
    buffer += "\t\"name\": " + parrot.GetName() + ",\n";
    buffer += "\t\"age\": " + std::to_string(parrot.GetAge()) + ",\n";
    buffer += "}";
}
