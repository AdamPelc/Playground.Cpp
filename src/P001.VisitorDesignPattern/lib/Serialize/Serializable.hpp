#pragma once
#ifndef PLAYGROUND_CPP_SERIALIZABLE_HPP
#define PLAYGROUND_CPP_SERIALIZABLE_HPP

#include <string>

#include "Serializer.hpp"

class Serializable {
public:
    [[nodiscard]] virtual std::string Serialize(const Serializer& serializer) const = 0;
};

#endif  // PLAYGROUND_CPP_SERIALIZABLE_HPP
