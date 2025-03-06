#pragma once

#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <cstdint>

template<typename T, typename TParameter>
class named_type_t
{
public:
    using value_type_t = T;

    named_type_t() = default;
    explicit named_type_t(T const& value) : m_value(value) {}
    explicit named_type_t(T&& value) : m_value(std::move(value)) {}


    operator T() const { return m_value; }

    T& get() { return m_value; }
    [[nodiscard]] const T& get() const { return m_value; }
private:
    T m_value{};
};

template<typename T>
struct named_type_hasher_t {
    std::size_t operator()(T const& obj) const noexcept {
        return std::hash<typename T::value_type_t>()(obj.get());
    }
};

struct pair_hasher_t {
    std::size_t operator()(std::pair<int, int> const& obj) const noexcept {
        return std::hash<int>()(obj.first) ^ std::hash<int>()(obj.second);
    }
};

using node_t = int;
using source_node_t = named_type_t<node_t, struct source_node_parameter_t>;
using destination_node_t = named_type_t<node_t, struct destination_node_parameter_t>;
using capacity_t = named_type_t<int, struct capacity_parameter_t>;
using flow_t = named_type_t<int, struct flow_parameter_t>;

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

class edge_data_t
{
public:
    edge_data_t() = delete;
    edge_data_t(const edge_data_t&) = delete;
    edge_data_t& operator=(const edge_data_t&) = delete;
    edge_data_t(edge_data_t&&) = delete;
    edge_data_t& operator=(edge_data_t&&) = delete;

    explicit edge_data_t(capacity_t capacity);

    capacity_t get_remaining_capacity() const;
    void augment(flow_t flow);

private:
    capacity_t m_capacity = {};
    flow_t m_flow = {};
};

class ford_fulkerson_dfs_solver_t
{
public:
    void add_edge(edge_t edge);
    std::uint64_t get_max_flow(source_node_t source, destination_node_t sink);

private:
    std::unordered_map<source_node_t, std::vector<destination_node_t>, named_type_hasher_t<source_node_t>> m_graph;
    std::unordered_map<std::pair<source_node_t, destination_node_t>, edge_data_t, pair_hasher_t> m_edges;
    std::unordered_set<node_t> m_visited;
    destination_node_t m_sink_node;

    flow_t dfs(source_node_t source, flow_t flow);
};
