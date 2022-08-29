#pragma once
#ifndef PLAYGROUND_CPP_JSONSERIALIZER_HPP
#define PLAYGROUND_CPP_JSONSERIALIZER_HPP

#include "Serialize/Serializer.hpp"

class JsonSerializer : public Serializer {
    std::string Serialize(const Cat& cat) const override;
    std::string Serialize(const Dog& dog) const override;
    std::string Serialize(const Parrot& parrot) const override;
};

#endif// PLAYGROUND_CPP_JSONSERIALIZER_HPP
