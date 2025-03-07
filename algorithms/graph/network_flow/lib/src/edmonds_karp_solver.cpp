#include "edmonds_karp_solver.hpp"

#include <limits>
#include <queue>
#include <stdexcept>
#include <unordered_set>

void edmonds_karp_solver_t::add_edge( edge_t edge ) {
    const auto from = edge.get_source();
    const auto to = edge.get_destination();

    // Insert information about (from) -> (to) connection
    m_graph[from].push_back(to);
    m_edges.emplace(std::make_pair(from, to), edge.get_capacity());

    // Insert information about (to) -> (from) residual connection
    m_graph[source_node_t(to)].emplace_back(from);
    m_edges.emplace(std::make_pair(source_node_t(to), destination_node_t(from)), capacity_t(0));
}

flow_t edmonds_karp_solver_t::get_max_flow(source_node_t source, destination_node_t sink) {
    if(source.get() == sink.get()) {
        return flow_t(0);
    }

    auto total_flow = flow_t(0);

    while(auto additional_flow = bfs(source, sink)) {
        total_flow.get() += additional_flow;
    }

    return total_flow;
}

flow_t edmonds_karp_solver_t::bfs(source_node_t source, destination_node_t sink) {
    std::unordered_map<destination_node_t, source_node_t, named_type_hasher_t<destination_node_t>> parents;
    std::unordered_set<source_node_t, named_type_hasher_t<source_node_t>> visited;

    std::queue<std::pair<source_node_t, flow_t>> queue;
    auto max_flow = flow_t(std::numeric_limits<flow_t::value_type_t>::max());
    queue.emplace(source, max_flow);

    while(!queue.empty()) {
        const auto [node, flow] = queue.front();
        queue.pop();

        if(node == sink) {
            max_flow = flow;
            break;
        }

        if(visited.find(node) != visited.end()) {
            continue;
        }
        visited.insert(node);


        for(auto& destination : m_graph.at(node)) {
            auto& edge = m_edges.at({node, destination});
            const auto remaining_capacity = edge.get_remaining_capacity();
            if(remaining_capacity == 0) {
                continue;
            }

            if(visited.find(source_node_t(destination)) != visited.end()) {
                continue;
            }

            parents[destination] = node;
            const auto min_flow = flow_t(std::min(flow.get(), remaining_capacity.get()));

            queue.emplace(destination_node_t(destination), min_flow);
        }
    }


    return flow_t();
}
