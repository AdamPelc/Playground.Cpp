#include <gtest/gtest.h>

#include "edmonds_karp_solver.hpp"
#include "ford_fulkerson_dfs_solver.hpp"

template <typename T>
class maximum_flow_test_t : public ::testing::Test {};

using solver_types_t = ::testing::Types<ford_fulkerson_dfs_solver_t, edmonds_karp_solver_t>;
TYPED_TEST_SUITE(maximum_flow_test_t, solver_types_t);

TYPED_TEST(maximum_flow_test_t, Scenario_1) {
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

    TypeParam solver;

    for (const auto& edge : edges) {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow(source_node_t('s'), destination_node_t('t'));

    ASSERT_EQ(actual_max_flow, 20);
}

TYPED_TEST(maximum_flow_test_t, Scenario_2) {
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

    TypeParam solver;

    for (const auto& edge : edges) {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow(source_node_t('s'), destination_node_t('t'));

    ASSERT_EQ(actual_max_flow, 23);
}

TYPED_TEST(maximum_flow_test_t, Scenario_3_DisconnectedGraph) {
    // Arrange
    std::array edges = {edge_t(source_node_t('s'), destination_node_t(0), capacity_t(10)),
                        edge_t(source_node_t(1), destination_node_t('t'), capacity_t(10))};

    TypeParam solver;

    for (const auto& edge : edges) {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow(source_node_t('s'), destination_node_t('t'));

    // Assert
    ASSERT_EQ(actual_max_flow, 0);  // No path from 's' to 't'
}

TYPED_TEST(maximum_flow_test_t, Scenario_4_SingleEdge) {
    // Arrange
    std::array edges = {edge_t(source_node_t('s'), destination_node_t('t'), capacity_t(10))};

    TypeParam solver;

    for (const auto& edge : edges) {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow(source_node_t('s'), destination_node_t('t'));

    // Assert
    ASSERT_EQ(actual_max_flow, 10);  // Direct edge from 's' to 't' carries full capacity
}

TYPED_TEST(maximum_flow_test_t, Scenario_5_Bottleneck) {
    // Arrange
    std::array edges = {edge_t(source_node_t('s'), destination_node_t(0), capacity_t(10)),
                        edge_t(source_node_t(0), destination_node_t(1), capacity_t(5)),
                        edge_t(source_node_t(1), destination_node_t('t'), capacity_t(10))};

    TypeParam solver;

    for (const auto& edge : edges) {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow(source_node_t('s'), destination_node_t('t'));

    // Assert
    ASSERT_EQ(actual_max_flow, 5);  // Bottleneck at capacity 5 between nodes 0 and 1
}

TYPED_TEST(maximum_flow_test_t, Scenario_6_SourceEqualToSink) {
    // Arrange
    TypeParam solver;

    // Act
    const auto actual_max_flow = solver.get_max_flow(source_node_t('s'), destination_node_t('s'));

    // Assert
    ASSERT_EQ(actual_max_flow, 0);  // No flow when source and sink are the same
}

TYPED_TEST(maximum_flow_test_t, Scenario_7_NegativeOrZeroCapacities) {
    // Arrange
    std::array edges = {
        edge_t(source_node_t('s'), destination_node_t(0), capacity_t(10)),
        edge_t(source_node_t(0), destination_node_t(1), capacity_t(0)),    // Zero capacity
        edge_t(source_node_t(1), destination_node_t('t'), capacity_t(-5))  // Negative capacity
    };

    ford_fulkerson_dfs_solver_t solver;

    for (const auto& edge : edges) {
        solver.add_edge(edge);
    }

    // Act
    const auto actual_max_flow = solver.get_max_flow(source_node_t('s'), destination_node_t('t'));

    // Assert
    ASSERT_EQ(actual_max_flow, 0);  // Zero or negative capacities should result in no flow
}
