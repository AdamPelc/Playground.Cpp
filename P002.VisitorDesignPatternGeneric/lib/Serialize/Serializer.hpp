#pragma once
#ifndef PLAYGROUND_CPP_SERIALIZER_HPP
#define PLAYGROUND_CPP_SERIALIZER_HPP

#include <string>

class Cat;
class Dog;
class Parrot;

class Serializer {
public:
    [[nodiscard]] virtual std::string Serialize( const Cat& cat ) const = 0;
    [[nodiscard]] virtual std::string Serialize( const Dog& dog ) const = 0;
    [[nodiscard]] virtual std::string Serialize( const Parrot& parrot ) const = 0;
};

#endif// PLAYGROUND_CPP_SERIALIZER_HPP
