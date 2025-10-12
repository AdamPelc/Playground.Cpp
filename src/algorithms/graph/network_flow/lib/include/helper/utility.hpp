#pragma once

#include <functional>
#include <utility>

struct pair_hasher_t {
    std::size_t operator()(std::pair<int, int> const& obj) const noexcept {
        return std::hash<int>()(obj.first) ^ std::hash<int>()(obj.second);
    }
};
