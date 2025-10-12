#include "edge.hpp"

edge_t::edge_t(source_node_t from, destination_node_t to, capacity_t capacity) : m_from(from), m_to(to), m_capacity
      (capacity) {}

source_node_t edge_t::get_source() const {
    return m_from;
}

destination_node_t edge_t::get_destination() const {
    return m_to;
}

capacity_t edge_t::get_capacity() const {
    return m_capacity;
}
