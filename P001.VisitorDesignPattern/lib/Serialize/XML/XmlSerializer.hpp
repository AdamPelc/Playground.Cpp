#pragma once
#ifndef PLAYGROUND_CPP_XMLSERIALIZER_HPP
#define PLAYGROUND_CPP_XMLSERIALIZER_HPP

#include "Serialize/Serializer.hpp"

class XmlSerializer : public Serializer {
    std::string Serialize(const Cat& cat) const override;
    std::string Serialize(const Dog& dog) const override;
    std::string Serialize(const Parrot& parrot) const override;
};

#endif// PLAYGROUND_CPP_XMLSERIALIZER_HPP
