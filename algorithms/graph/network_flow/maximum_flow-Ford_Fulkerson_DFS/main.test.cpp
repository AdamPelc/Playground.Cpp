#include <gtest/gtest.h>

#include "maximum_flow.hpp"

TEST(Maximum_Flow_Ford_Fulkerson_DFS, Scenario_1)
{
    // Arrange
    std::array edges = {
            edge_t('s', 0, 10),
            edge_t('s', 1, 10),
            edge_t(0, 2, 25),
            edge_t(1, 3, 15),
            edge_t(2, 't', 10),
            edge_t(3, 0, 6),
            edge_t(3, 't', 10),
    };

    ford_fulkerson_dfs_solver_t solver;

    for(const auto& edge : edges)
    {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow('s', 't');

    ASSERT_EQ(actual_max_flow, 20);
}

TEST(Maximum_Flow_Ford_Fulkerson_DFS, Scenario_2)
{
    // Arrange
    std::array edges = {
        edge_t('s', 0, 10),
        edge_t('s', 1, 5),
        edge_t('s', 2, 10),
        edge_t(0, 3, 10),
        edge_t(1, 2, 10),
        edge_t(2, 5, 15),
        edge_t(3, 1, 20),
        edge_t(3, 6, 15),
        edge_t(4, 1, 15),
        edge_t(4, 3, 3),
        edge_t(5, 4, 4),
        edge_t(5, 8, 10),
        edge_t(6, 7, 10),
        edge_t(6, 't', 15),
        edge_t(7, 4, 10),
        edge_t(7, 5, 7),
        edge_t(8, 't', 10),
    };

    ford_fulkerson_dfs_solver_t solver;

    for(const auto& edge : edges)
    {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow('s', 't');

    ASSERT_EQ(actual_max_flow, 23);
}