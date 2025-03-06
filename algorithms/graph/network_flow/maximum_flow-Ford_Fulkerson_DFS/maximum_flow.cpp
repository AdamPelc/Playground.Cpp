#include <stdexcept>
#include <limits>
#include <iostream>
#include <fmt/format.h>
#include "maximum_flow.hpp"

edge_t::edge_t(int from, int to, int capacity) : m_from(from), m_to(to), m_capacity(capacity) {}

int edge_t::get_from() const {
    return m_from;
}

int edge_t::get_to() const {
    return m_to;
}

int edge_t::get_capacity() const {
    return m_capacity;
}

int edge_t::get_remaining_capacity() const {
    return m_capacity - m_flow;
}

void edge_t::add_flow(int flow) {
    if(flow > get_remaining_capacity()) {
        throw std::invalid_argument("flow is greater than remaining capacity");
    }
}

void ford_fulkerson_dfs_solver_t::add_edge(edge_t edge) {
    const auto from = edge.get_from();
    const auto to = edge.get_to();

    // Insert information about (from) -> (to) connection
    m_graph[from].push_back(to);
    m_edges.emplace(std::make_pair(from, to), edge.get_capacity());

    // Insert information about (to) -> (from) residual connection
    m_graph[to].push_back(from);
    m_edges.emplace(std::make_pair(to, from), 0);
}

std::uint64_t ford_fulkerson_dfs_solver_t::get_max_flow(int source, int sink) {
    int max_flow = 0;

    std::cout << "----\n";
    while(auto current_flow = dfs(source, sink, std::numeric_limits<int>::max())) {
        max_flow += current_flow;
        m_visited.clear();
        fmt::print("max_flow={}, current_flow={}\n", max_flow,current_flow);
    }

    return max_flow;
}

int ford_fulkerson_dfs_solver_t::dfs(int source, int sink, int flow) {
    if(source == sink) {
        return flow;
    }

    m_visited.insert(source);

    for(auto& destination : m_graph.at(source)) {
        if(m_visited.find(destination) != m_visited.end()) {
            continue;
        }

        auto& edge = m_edges.at({source, destination});
        const auto remaining_capacity = edge.get_remaining_capacity();
        if(remaining_capacity == 0) {
            continue;
        }

        const auto min_flow = std::min(flow, remaining_capacity);
        fmt::print("source={}, destination={}, remaining_capacity={}, min_flow={}\n", source, destination,
                   remaining_capacity, min_flow);
        const auto bottleneck = dfs(destination, sink, min_flow);

        if(bottleneck > 0) {
            // Add flow to this
            edge.augment(bottleneck);

            // Add negative flow
            auto& residual_edge = m_edges.at({destination, source});
            residual_edge.augment(-flow);
            return bottleneck;
        }
    }
    return 0;
}

edge_data_t::edge_data_t(int capacity) : m_capacity(capacity) {}

int edge_data_t::get_remaining_capacity() const {
    return m_capacity - m_flow;
}

void edge_data_t::augment(int flow) {
    m_flow += flow;
}
