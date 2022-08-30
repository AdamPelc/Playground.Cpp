#include "Dog.hpp"

Dog::Dog(std::string_view name, std::size_t age) : name(name), age(age) {};

std::string Dog::GetName() const {
    return std::string(name);
}

std::size_t Dog::GetAge() const {
    return age;
}

std::string Dog::Serialize(const Serializer& serializer) const {
    return serializer.Serialize( *this );
}
