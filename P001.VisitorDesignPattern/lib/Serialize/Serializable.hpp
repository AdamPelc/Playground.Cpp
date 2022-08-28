#pragma once
#ifndef PLAYGROUND_CPP_SERIALIZABLE_HPP
#define PLAYGROUND_CPP_SERIALIZABLE_HPP

#include "Serializer.hpp"

#include <string>

class Serializable {
public:
    virtual std::string Serialize(Serializer& serializer) = 0;
};

#endif// PLAYGROUND_CPP_SERIALIZABLE_HPP
