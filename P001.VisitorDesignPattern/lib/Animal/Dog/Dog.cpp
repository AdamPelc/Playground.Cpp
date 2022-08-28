#include "Dog.hpp"

constexpr Dog::Dog(std::string_view name, std::size_t age) noexcept : name(name), age(age) {};

std::string Dog::Serialize(Serializer& serializer) {
    return serializer.SerializeDog(*this);
}
