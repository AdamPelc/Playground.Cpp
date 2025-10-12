#pragma once
#ifndef PLAYGROUND_CPP_PARROT_HPP
#define PLAYGROUND_CPP_PARROT_HPP

#include <string>
#include <string_view>

#include "Animal/Helper/Visitor/VisitableAnimal.hpp"

class Parrot : public VisitableAnimal<Parrot> {
public:
    Parrot(std::string_view name, std::size_t age);

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] std::size_t GetAge() const;

private:
    std::string name;
    std::size_t age;
};

#endif  // PLAYGROUND_CPP_PARROT_HPP
