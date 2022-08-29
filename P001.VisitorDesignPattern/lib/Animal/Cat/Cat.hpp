#pragma once
#ifndef PLAYGROUND_CPP_CAT_HPP
#define PLAYGROUND_CPP_CAT_HPP

#include "Serialize/Serializable.hpp"

#include <string_view>
#include <cstdint>

class Cat : public Serializable {
public:
    Cat(std::string_view name, std::size_t age);

    std::string GetName() const;
    std::size_t GetAge() const;

    std::string Serialize(const Serializer& serializer) override;
private:
    std::string name;
    std::size_t age;

    friend class Serializer;
};


#endif// PLAYGROUND_CPP_CAT_HPP
