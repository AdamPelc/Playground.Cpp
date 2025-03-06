#include "edge_throughput.hpp"

edge_throughput_t::edge_throughput_t(capacity_t capacity) : m_capacity(capacity) {}

capacity_t edge_throughput_t::get_remaining_capacity() const {
    return capacity_t(m_capacity.get() - m_flow.get());
}

void edge_throughput_t::augment(flow_t flow) {
    m_flow.get() += flow;
}