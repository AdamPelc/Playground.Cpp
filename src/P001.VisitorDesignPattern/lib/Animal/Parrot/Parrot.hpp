#pragma once
#ifndef PLAYGROUND_CPP_PARROT_HPP
#define PLAYGROUND_CPP_PARROT_HPP

#include <string_view>

#include "Serialize/Serializable.hpp"
#include "Serialize/Serializer.hpp"

class Parrot : public Serializable {
public:
    Parrot(std::string_view name, std::size_t age);

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] std::size_t GetAge() const;

    [[nodiscard]] std::string Serialize(const Serializer& serializer) const override;

private:
    std::string name;
    std::size_t age;
};

#endif  // PLAYGROUND_CPP_PARROT_HPP
