#pragma once
#ifndef PLAYGROUND_CPP_JSONSERIALIZER_HPP
#define PLAYGROUND_CPP_JSONSERIALIZER_HPP

#include "Serialize/Serializer/Serializer.hpp"

#include <string>

class Cat;
class Dog;
class Parrot;

class JsonSerializer : public Serializer {
public:
    void Visit( const Cat& cat ) override;
    void Visit( const Dog& dog ) override;
    void Visit( const Parrot& parrot ) override;
};

#endif// PLAYGROUND_CPP_JSONSERIALIZER_HPP
