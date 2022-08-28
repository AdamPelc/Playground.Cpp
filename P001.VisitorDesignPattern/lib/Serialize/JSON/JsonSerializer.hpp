#pragma once
#ifndef PLAYGROUND_CPP_JSONSERIALIZER_HPP
#define PLAYGROUND_CPP_JSONSERIALIZER_HPP

#include "Serialize/Serializer.hpp"

class JsonSerializer : public Serializer {
    std::string SerializeCat(const Cat& cat) override;
    std::string SerializeDog(const Dog& dog) override;
};

#endif// PLAYGROUND_CPP_JSONSERIALIZER_HPP
