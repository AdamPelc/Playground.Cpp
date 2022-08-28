#pragma once
#ifndef PLAYGROUND_CPP_CAT_HPP
#define PLAYGROUND_CPP_CAT_HPP

#include <string_view>
#include <cstdint>

class Cat {
public:
    constexpr explicit Cat(std::string_view name, std::size_t age) noexcept;
private:
    std::string_view name;
    std::size_t age;
};


#endif// PLAYGROUND_CPP_CAT_HPP
