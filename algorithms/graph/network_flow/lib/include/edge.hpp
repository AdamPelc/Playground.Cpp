#pragma once

#include "types.hpp"

class edge_t
{
public:
    edge_t(source_node_t from, destination_node_t to, capacity_t capacity);

    [[nodiscard]] source_node_t get_source() const;
    [[nodiscard]] destination_node_t get_destination() const;
    [[nodiscard]] capacity_t get_capacity() const;

private:
    source_node_t m_from = {};
    destination_node_t m_to = {};
    capacity_t m_capacity = {};
};
