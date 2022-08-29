#include "Cat.hpp"

Cat::Cat(std::string_view name, std::size_t age) : name(name), age(age) {}

std::string Cat::GetName() const {
    return std::string(name);
}

std::size_t Cat::GetAge() const {
    return age;
}

std::string Cat::Serialize(const Serializer& serializer) {
    return serializer.SerializeCat(*this);
}
