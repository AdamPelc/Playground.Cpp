#pragma once
#ifndef PLAYGROUND_CPP_DOG_HPP
#define PLAYGROUND_CPP_DOG_HPP

#include <string_view>
#include <cstdint>

class Dog {
public:
    constexpr explicit Dog(std::string_view name, std::size_t age) noexcept;
private:
    std::string_view name;
    std::size_t age;
};


#endif// PLAYGROUND_CPP_DOG_HPP
