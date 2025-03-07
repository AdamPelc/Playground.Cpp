#include "ford_fulkerson_dfs_solver.hpp"

#include <limits>

void ford_fulkerson_dfs_solver_t::add_edge(edge_t edge) {
    const auto from = edge.get_source();
    const auto to = edge.get_destination();

    // Insert information about (from) -> (to) connection
    m_graph[from].push_back(to);
    m_edges.emplace(std::make_pair(from, to), edge.get_capacity());

    // Insert information about (to) -> (from) residual connection
    m_graph[source_node_t(to)].emplace_back(from);
    m_edges.emplace(std::make_pair(source_node_t(to), destination_node_t(from)), capacity_t(0));
}

flow_t ford_fulkerson_dfs_solver_t::get_max_flow(source_node_t source, destination_node_t sink) {
    if(source.get() == sink.get()) {
        return flow_t(0);
    }

    m_sink_node = sink;
    auto max_flow = flow_t(0);

    while(auto additional_flow = dfs(source, flow_t(std::numeric_limits<flow_t::value_type_t>::max()))) {
        max_flow.get() += additional_flow;
        m_visited.clear();
    }

    return max_flow;
}

flow_t ford_fulkerson_dfs_solver_t::dfs(source_node_t source, flow_t flow) {
    if(source.get() == m_sink_node.get()) {
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

        const auto min_flow = flow_t(std::min(flow.get(), remaining_capacity.get()));
        const auto bottleneck = dfs(source_node_t(destination), min_flow);

        if(bottleneck > 0) {
            // Add flow to this
            edge.augment(bottleneck);

            // Add negative flow
            auto& residual_edge = m_edges.at({source_node_t(destination), destination_node_t(source)});
            residual_edge.augment(flow_t(-flow.get()));
            return bottleneck;
        }
    }
    return flow_t(0);
}
