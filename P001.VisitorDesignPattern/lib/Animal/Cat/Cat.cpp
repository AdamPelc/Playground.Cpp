#include "Cat.hpp"

constexpr Cat::Cat(std::string_view name, std::size_t age) noexcept : name(name), age(age) {}

std::string Cat::Serialize(Serializer& serializer) {
    return serializer.SerializeCat(*this);
}
