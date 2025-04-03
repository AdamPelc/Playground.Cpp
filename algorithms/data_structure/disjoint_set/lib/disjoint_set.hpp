#pragma once

#include <cstddef>

class disjoint_set {
public:
    explicit disjoint_set(std::size_t number_of_nodes);

    std::size_t find(std::size_t node);

    void unite(std::size_t node_a, std::size_t node_b);
};
