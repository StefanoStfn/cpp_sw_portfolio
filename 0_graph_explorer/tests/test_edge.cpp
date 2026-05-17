//
// Testing the Edge Class
// BasicEdgeInstantiation --> single object creation and testing
// StoresCorrectValuesInsideVector --> vector of edges creation and testing
//

#include <gtest/gtest.h>
#include "edge.h"
#include <vector>

namespace {

    TEST(EdgeTest, BasicEdgeInstantiation) {
        // weight, node id
        const edge edge_sample{3, 4};
        EXPECT_EQ(3, edge_sample.get_weight());
        EXPECT_EQ(4, edge_sample.get_node_id());
    }

    TEST(EdgeTest, StoresCorrectValuesInsideVector) {
        std::vector<edge> edge_sample;
        for (int i = 0; i < 10; ++i)
        {
            edge_sample.emplace_back(
                i, i*2
            );
        }
        EXPECT_EQ(0, edge_sample[0].get_node_id());
        EXPECT_EQ(0, edge_sample[0].get_weight());
        EXPECT_EQ(4, edge_sample[2].get_node_id());
        EXPECT_EQ(2, edge_sample[2].get_weight());
        EXPECT_EQ(16, edge_sample[8].get_node_id());
        EXPECT_EQ(8, edge_sample[8].get_weight());
    }
}