#pragma once
#ifndef PLAYGROUND_CPP_DOG_HPP
#define PLAYGROUND_CPP_DOG_HPP

#include "Serialize/Serializable.hpp"

#include <string_view>
#include <cstdint>

class Dog : public Serializable {
public:
    constexpr explicit Dog(std::string_view name, std::size_t age) noexcept;

    std::string Serialize(Serializer& serializer) override;
private:
    std::string_view name;
    std::size_t age;
};


#endif// PLAYGROUND_CPP_DOG_HPP
