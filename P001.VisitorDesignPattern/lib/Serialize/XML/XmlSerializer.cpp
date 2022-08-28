#include "XmlSerializer.hpp"

#include "Animal/Cat/Cat.hpp"
#include "Animal/Dog/Dog.hpp"

std::string XmlSerializer::SerializeCat(const Cat& cat) {
    using namespace std::string_literals;

    std::string response;
    response += "<animal>\n";
    response += "\t<species>Cat</species>\n";
    response += "\t<name>" + cat.GetName() + "</name>\n";
    response += "\t<age>" + std::to_string(cat.GetAge()) + "</age>\n";
    response += "</animal>";

    return response;
}

std::string XmlSerializer::SerializeDog(const Dog& dog) {
    using namespace std::string_literals;

    std::string response;
    response += "<animal>\n";
    response += "\t<species>Dog</species>\n";
    response += "\t<name>" + dog.GetName() + "</name>\n";
    response += "\t<age>" + std::to_string(dog.GetAge()) + "</age>\n";
    response += "</animal>";

    return response;
}
