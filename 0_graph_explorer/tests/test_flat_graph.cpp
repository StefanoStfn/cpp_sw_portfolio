//
// Testing the Graph Class
// Matrix1Test --> distance checks and path checks in a hand-defined matrix
// Matrix2Test --> results checks for edge case: no path between selected nodes
//

#include <gtest/gtest.h>
#include "graph_flat.h"

namespace
{
    // Declaration of Fixture --> adjacency matrix creation and releasing
    class GraphFlatTest : public ::testing::Test
    {
        protected:
            static constexpr int node_number = 4;
            int** adjacency_matrix = nullptr;
            std::pair<std::vector<int>, int> dijkstra_outcome;
            void TearDown() override
            {
                for (int i = 0; i < node_number; ++i)
                {
                    delete[] adjacency_matrix[i];
                }
                delete[] adjacency_matrix;
            }
    };

    TEST_F(GraphFlatTest, FlatMatrix1Test)
    {
        adjacency_matrix = new int*[node_number];
        adjacency_matrix[0] = new int[node_number]{0,2,1,4};
        adjacency_matrix[1] = new int[node_number]{2,0,1,0};
        adjacency_matrix[2] = new int[node_number]{1,1,0,2};
        adjacency_matrix[3] = new int[node_number]{4,0,2,0};
        const GraphFlat graph_sample{adjacency_matrix, node_number};
        EXPECT_EQ(
            graph_sample.get_edge_targets(),
            (std::vector<int>{1,2,3,0,2,0,1,3,0,2})
        );
        EXPECT_EQ(
            graph_sample.get_edge_weights(),
            (std::vector<int>{2,1,4,2,1,1,1,2,4,2})
        );
        EXPECT_EQ(
            graph_sample.get_offsets(),
            (std::vector<int>{0,3,5,8,10})
            );
        dijkstra_outcome = graph_sample.lazy_dijkstra(1, 0);
        EXPECT_EQ(2, dijkstra_outcome.second);
        std::vector<int> outcome_vect{1,0};
        EXPECT_EQ(outcome_vect, dijkstra_outcome.first);

        dijkstra_outcome = graph_sample.lazy_dijkstra(3, 0);
        EXPECT_EQ(3, dijkstra_outcome.second);
        outcome_vect = {3,2,0};
        EXPECT_EQ(outcome_vect, dijkstra_outcome.first);
    }

    TEST_F(GraphFlatTest, FlatMatrix2Test)
    {
        adjacency_matrix = new int*[node_number];
        adjacency_matrix[0] = new int[node_number]{0,2,1,4};
        adjacency_matrix[1] = new int[node_number]{2,0,1,0};
        adjacency_matrix[2] = new int[node_number]{1,1,0,2};
        adjacency_matrix[3] = new int[node_number]{0,0,0,0};

        const GraphFlat graph_sample{adjacency_matrix, node_number};
        EXPECT_EQ(
            graph_sample.get_edge_targets(),
            (std::vector<int>{1,2,3,0,2,0,1,3})
        );
        EXPECT_EQ(
            graph_sample.get_edge_weights(),
            (std::vector<int>{2,1,4,2,1,1,1,2})
        );
        EXPECT_EQ(
            graph_sample.get_offsets(),
            (std::vector<int>{0,3,5,8,8})
            );
        dijkstra_outcome = graph_sample.lazy_dijkstra(3,1);
        EXPECT_EQ(INT_MAX, dijkstra_outcome.second);
        std::vector<int> outcome_vect{1};
        EXPECT_EQ(outcome_vect, dijkstra_outcome.first);
    }
}
