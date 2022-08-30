#pragma once
#ifndef PLAYGROUND_CPP_PARROT_HPP
#define PLAYGROUND_CPP_PARROT_HPP

#include "Animal/Helper/Visitor/VisitableAnimal.hpp"

#include <string_view>
#include <string>

class Parrot : public VisitableAnimal<Parrot> {
public:
    Parrot( std::string_view name, std::size_t age );

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] std::size_t GetAge() const;

private:
    std::string name;
    std::size_t age;
};


#endif// PLAYGROUND_CPP_PARROT_HPP
