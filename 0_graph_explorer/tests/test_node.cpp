//
// Testing the Node Class
// NoNeighborBehaviour --> instantiating a node without neighbors
// ValidNeighborsChecking --> instantiate a node and checks if zero-weight connections are discarded
// NeighborsCheckingWithNegativeWeights --> instantiate a node and checks if zero-and-negative-weight connections are discarded
//

#include <gtest/gtest.h>
#include "node.h"

namespace
{
    TEST(NodeTest, NoNeighborBehaviour)
    {
        const int* neighbors_array = nullptr;
        const node node_sample{neighbors_array, 1, 0};
        EXPECT_EQ(0, node_sample.get_edge_vect().size());
        EXPECT_EQ(1, node_sample.get_id());
    }

    TEST(NodeTest, ValidNeighborsChecking)
    {
        const int neighbors_array[5] = {1,4,0,7,8};
        const node node_sample{neighbors_array, 1, 5};
        EXPECT_EQ(4, node_sample.get_edge_vect().size());
        EXPECT_EQ(1, node_sample.get_id());
        // validating edges weight and ids, index 2 creation is skipped because 0 weight
        EXPECT_EQ(0, node_sample.get_edge_vect()[0].get_node_id());
        EXPECT_EQ(1, node_sample.get_edge_vect()[0].get_weight());
        EXPECT_EQ(3, node_sample.get_edge_vect()[2].get_node_id());
        EXPECT_EQ(7, node_sample.get_edge_vect()[2].get_weight());
        EXPECT_EQ(4, node_sample.get_edge_vect()[3].get_node_id());
        EXPECT_EQ(8, node_sample.get_edge_vect()[3].get_weight());
    }

    TEST(NodeTest, NeighborsCheckingWithNegativeWeights)
    {
        constexpr int node_number = 6;
        constexpr int neighbors_array[node_number] = {-1,4,0,7,-8,10};
        const node node_sample{neighbors_array, 1, node_number};
        // Expected 3 elements
        EXPECT_EQ(3, node_sample.get_edge_vect().size());
        EXPECT_EQ(1, node_sample.get_id());
        // index 0,2,4 are skipped because lower equal than 0
        EXPECT_EQ(1, node_sample.get_edge_vect()[0].get_node_id());
        EXPECT_EQ(4, node_sample.get_edge_vect()[0].get_weight());
        EXPECT_EQ(3, node_sample.get_edge_vect()[1].get_node_id());
        EXPECT_EQ(7, node_sample.get_edge_vect()[1].get_weight());
        EXPECT_EQ(5, node_sample.get_edge_vect()[2].get_node_id());
        EXPECT_EQ(10, node_sample.get_edge_vect()[2].get_weight());
    }
}
