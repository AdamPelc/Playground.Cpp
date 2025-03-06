#include <gtest/gtest.h>

#include "maximum_flow.hpp"

TEST(Maximum_Flow_Ford_Fulkerson_DFS, Scenario_1)
{
    // Arrange
    std::array edges = {
            edge_t(source_node_t('s'), destination_node_t(0), capacity_t(10)),
            edge_t(source_node_t('s'), destination_node_t(1), capacity_t(10)),
            edge_t(source_node_t(0), destination_node_t(2), capacity_t(25)),
            edge_t(source_node_t(1), destination_node_t(3), capacity_t(15)),
            edge_t(source_node_t(2), destination_node_t('t'), capacity_t(10)),
            edge_t(source_node_t(3), destination_node_t(0), capacity_t(6)),
            edge_t(source_node_t(3), destination_node_t('t'), capacity_t(10)),
    };

    ford_fulkerson_dfs_solver_t solver;

    for(const auto& edge : edges)
    {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow(source_node_t('s'), destination_node_t('t'));

    ASSERT_EQ(actual_max_flow, 20);
}

TEST(Maximum_Flow_Ford_Fulkerson_DFS, Scenario_2)
{
    // Arrange
    std::array edges = {
        edge_t(source_node_t('s'), destination_node_t(0), capacity_t(10)),
        edge_t(source_node_t('s'), destination_node_t(1), capacity_t(5)),
        edge_t(source_node_t('s'), destination_node_t(2), capacity_t(10)),
        edge_t(source_node_t(0), destination_node_t(3), capacity_t(10)),
        edge_t(source_node_t(1), destination_node_t(2), capacity_t(10)),
        edge_t(source_node_t(2), destination_node_t(5), capacity_t(15)),
        edge_t(source_node_t(3), destination_node_t(1), capacity_t(20)),
        edge_t(source_node_t(3), destination_node_t(6), capacity_t(15)),
        edge_t(source_node_t(4), destination_node_t(1), capacity_t(15)),
        edge_t(source_node_t(4), destination_node_t(3), capacity_t(3)),
        edge_t(source_node_t(5), destination_node_t(4), capacity_t(4)),
        edge_t(source_node_t(5), destination_node_t(8), capacity_t(10)),
        edge_t(source_node_t(6), destination_node_t(7), capacity_t(10)),
        edge_t(source_node_t(6), destination_node_t('t'), capacity_t(15)),
        edge_t(source_node_t(7), destination_node_t(4), capacity_t(10)),
        edge_t(source_node_t(7), destination_node_t(5), capacity_t(7)),
        edge_t(source_node_t(8), destination_node_t('t'), capacity_t(10)),
    };

    ford_fulkerson_dfs_solver_t solver;

    for(const auto& edge : edges)
    {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow(source_node_t('s'), destination_node_t('t'));

    ASSERT_EQ(actual_max_flow, 23);
}