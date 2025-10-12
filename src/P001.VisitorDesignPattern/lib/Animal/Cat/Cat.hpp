#pragma once
#ifndef PLAYGROUND_CPP_CAT_HPP
#define PLAYGROUND_CPP_CAT_HPP

#include <cstdint>
#include <string_view>

#include "Serialize/Serializable.hpp"

class Cat : public Serializable {
public:
    Cat(std::string_view name, std::size_t age);

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] std::size_t GetAge() const;

    [[nodiscard]] std::string Serialize(const Serializer& serializer) const override;

private:
    std::string name;
    std::size_t age;

    friend class Serializer;
};

#endif  // PLAYGROUND_CPP_CAT_HPP
