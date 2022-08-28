#pragma once
#ifndef PLAYGROUND_CPP_DOG_HPP
#define PLAYGROUND_CPP_DOG_HPP

#include <string_view>

class Dog {
public:
    constexpr explicit Dog(std::string_view name) noexcept;
private:
    std::string_view name;
};


#endif// PLAYGROUND_CPP_DOG_HPP
