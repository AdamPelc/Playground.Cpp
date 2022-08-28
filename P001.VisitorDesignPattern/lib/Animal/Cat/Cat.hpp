#pragma once
#ifndef PLAYGROUND_CPP_CAT_HPP
#define PLAYGROUND_CPP_CAT_HPP

#include <string_view>

class Cat {
public:
    constexpr explicit Cat(std::string_view name) noexcept;
private:
    std::string_view name;
};


#endif// PLAYGROUND_CPP_CAT_HPP
