#include "Parrot.hpp"

Parrot::Parrot( std::string_view name, std::size_t age ) : name(name), age(age) {}

std::string Parrot::GetName() const {
    return {name};
}

std::size_t Parrot::GetAge() const {
    return age;
}

std::string Parrot::Serialize( Serializer& serializer ) {
    return serializer.SerializeParrot(*this);
}
