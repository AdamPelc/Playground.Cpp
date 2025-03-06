#pragma once

#include <utility>
#include <functional>

struct pair_hasher_t {
    std::size_t operator()(std::pair<int, int> const& obj) const noexcept {
        return std::hash<int>()(obj.first) ^ std::hash<int>()(obj.second);
    }
};
