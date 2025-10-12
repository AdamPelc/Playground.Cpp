#include "XmlSerializer.hpp"

#include "Animal/Cat/Cat.hpp"
#include "Animal/Dog/Dog.hpp"
#include "Animal/Parrot/Parrot.hpp"

std::string XmlSerializer::Serialize(const Cat& cat) const {
    using namespace std::string_literals;

    std::string response;
    response += "<animal>\n";
    response += "\t<species>Cat</species>\n";
    response += "\t<name>" + cat.GetName() + "</name>\n";
    response += "\t<age>" + std::to_string(cat.GetAge()) + "</age>\n";
    response += "</animal>";

    return response;
}

std::string XmlSerializer::Serialize(const Dog& dog) const {
    using namespace std::string_literals;

    std::string response;
    response += "<animal>\n";
    response += "\t<species>Dog</species>\n";
    response += "\t<name>" + dog.GetName() + "</name>\n";
    response += "\t<age>" + std::to_string(dog.GetAge()) + "</age>\n";
    response += "</animal>";

    return response;
}

std::string XmlSerializer::Serialize(const Parrot& parrot) const {
    using namespace std::string_literals;

    std::string response;
    response += "<animal>\n";
    response += "\t<species>Parrot</species>\n";
    response += "\t<name>" + parrot.GetName() + "</name>\n";
    response += "\t<age>" + std::to_string(parrot.GetAge()) + "</age>\n";
    response += "</animal>";

    return response;
}
