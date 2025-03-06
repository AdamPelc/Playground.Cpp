#pragma once

#include "types.hpp"

class edge_throughput_t {
public:
    edge_throughput_t() = delete;
    edge_throughput_t(const edge_throughput_t&) = delete;
    edge_throughput_t& operator=(const edge_throughput_t&) = delete;
    edge_throughput_t( edge_throughput_t&&) = delete;
    edge_throughput_t& operator=(edge_throughput_t&&) = delete;

    explicit edge_throughput_t(capacity_t capacity);

    [[nodiscard]] capacity_t get_remaining_capacity() const;
    void augment(flow_t flow);

private:
    capacity_t m_capacity = {};
    flow_t m_flow = {};
};