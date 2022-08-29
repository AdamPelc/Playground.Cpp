#pragma once
#ifndef PLAYGROUND_CPP_XMLSERIALIZER_HPP
#define PLAYGROUND_CPP_XMLSERIALIZER_HPP

#include "Serialize/Serializer.hpp"

class XmlSerializer : public Serializer {
    std::string SerializeCat(const Cat& cat) override;
    std::string SerializeDog(const Dog& dog) override;
    std::string SerializeParrot(const Parrot& parrot) override;
};

#endif// PLAYGROUND_CPP_XMLSERIALIZER_HPP
