#pragma once
#ifndef PLAYGROUND_CPP_DOG_HPP
#define PLAYGROUND_CPP_DOG_HPP

#include "Serialize/Serializable.hpp"

#include <string_view>
#include <cstdint>

class Dog : public Serializable {
public:
    Dog(std::string_view name, std::size_t age);

    std::string GetName() const;
    std::size_t GetAge() const;

    std::string Serialize(const Serializer& serializer) const override;
private:
    std::string name;
    std::size_t age;
};


#endif// PLAYGROUND_CPP_DOG_HPP
