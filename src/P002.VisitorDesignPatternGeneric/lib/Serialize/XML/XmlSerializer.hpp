#pragma once
#ifndef PLAYGROUND_CPP_XMLSERIALIZER_HPP
#define PLAYGROUND_CPP_XMLSERIALIZER_HPP

#include <string>

#include "Serialize/Serializer/Serializer.hpp"

class Cat;
class Dog;
class Parrot;

class XmlSerializer : public Serializer {
public:
    void Visit(const Cat& cat) override;
    void Visit(const Dog& dog) override;
    void Visit(const Parrot& parrot) override;
};

#endif  // PLAYGROUND_CPP_XMLSERIALIZER_HPP
