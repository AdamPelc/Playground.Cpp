#pragma once
#ifndef PLAYGROUND_CPP_SERIALIZER_HPP
#define PLAYGROUND_CPP_SERIALIZER_HPP

#include "Animal/Helper/Visitor/AnimalVisitor.hpp"

#include <string>

class Serializer : public AnimalVisitor {
public:
    [[nodiscard]] std::string Serialize() const;

protected:
    std::string buffer;
};


#endif// PLAYGROUND_CPP_SERIALIZER_HPP
