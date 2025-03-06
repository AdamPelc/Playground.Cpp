#pragma once

#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <cstdint>

class edge_t
{
public:
    // TODO: Change types to be strongly typed
    edge_t(int from, int to, int capacity);

    int get_from() const;
    int get_to() const;
    int get_capacity() const;
    int get_remaining_capacity() const;
    void add_flow(int flow);

private:
    int m_from = {};
    int m_to = {};
    int m_capacity = {};
    int m_flow = {};
};

class edge_data_t
{
public:
    edge_data_t() = delete;
    edge_data_t(const edge_data_t&) = delete;
    edge_data_t& operator=(const edge_data_t&) = delete;
    edge_data_t(edge_data_t&&) = delete;
    edge_data_t& operator=(edge_data_t&&) = delete;

    explicit edge_data_t(int capacity);

    int get_remaining_capacity() const;
    void augment(int flow);

private:
    int m_capacity = {};
    int m_flow = {};
};

class ford_fulkerson_dfs_solver_t
{
public:
    void add_edge(edge_t edge);
    std::uint64_t get_max_flow(int source, int sink);
private:
    using source_node_t = int;
    using destination_node_t = int;

    // TODO: Maybe std::deque might replace std::vector
    std::unordered_map<source_node_t, std::vector<destination_node_t>> m_graph;
    std::map<std::pair<source_node_t, destination_node_t>, edge_data_t> m_edges;
    std::unordered_set<source_node_t> m_visited;

    int dfs(int source, int sink, int flow);
};
