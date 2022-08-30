#include "XmlSerializer.hpp"

#include "Animal/Animals/Cat/Cat.hpp"
#include "Animal/Animals/Dog/Dog.hpp"
#include "Animal/Animals/Parrot/Parrot.hpp"

void XmlSerializer::Visit( const Cat& cat ) {
    using namespace std::string_literals;

    buffer.clear();
    buffer += "<animal>\n";
    buffer += "\t<species>Cat</species>\n";
    buffer += "\t<name>" + cat.GetName() + "</name>\n";
    buffer += "\t<age>" + std::to_string( cat.GetAge() ) + "</age>\n";
    buffer += "</animal>";
}

void XmlSerializer::Visit( const Dog& dog ) {
    using namespace std::string_literals;

    buffer.clear();
    buffer += "<animal>\n";
    buffer += "\t<species>Dog</species>\n";
    buffer += "\t<name>" + dog.GetName() + "</name>\n";
    buffer += "\t<age>" + std::to_string( dog.GetAge() ) + "</age>\n";
    buffer += "</animal>";
}

void XmlSerializer::Visit( const Parrot& parrot ) {
    using namespace std::string_literals;

    buffer.clear();
    buffer += "<animal>\n";
    buffer += "\t<species>Parrot</species>\n";
    buffer += "\t<name>" + parrot.GetName() + "</name>\n";
    buffer += "\t<age>" + std::to_string( parrot.GetAge() ) + "</age>\n";
    buffer += "</animal>";
}
