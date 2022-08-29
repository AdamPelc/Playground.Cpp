#pragma once
#ifndef PLAYGROUND_CPP_SERIALIZER_HPP
#define PLAYGROUND_CPP_SERIALIZER_HPP

#include <string>

class Cat;
class Dog;
class Parrot;

class Serializer {
public:
    virtual std::string SerializeCat(const Cat& cat) const = 0;
    virtual std::string SerializeDog(const Dog& dog) const = 0;
    virtual std::string SerializeParrot( const Parrot& parrot ) const = 0;
};

#endif// PLAYGROUND_CPP_SERIALIZER_HPP
