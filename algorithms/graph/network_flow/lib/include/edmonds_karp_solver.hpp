#pragma once

#include "edge.hpp"
#include "edge_throughput.hpp"
#include "helper/utility.hpp"

class edmonds_karp_solver_t {
public:
    void add_edge(edge_t edge);
    flow_t get_max_flow(source_node_t source, destination_node_t sink);

private:
    std::unordered_map<source_node_t, std::vector<destination_node_t>, named_type_hasher_t<source_node_t>> m_graph;
    std::unordered_map<std::pair<source_node_t, destination_node_t>, edge_throughput_t, pair_hasher_t> m_edges;

    flow_t bfs(source_node_t source, destination_node_t sink);
};
