//
// Testing the Graph Class
// Matrix1Test --> distance checks and path checks in a hand-defined matrix
// Matrix2Test --> results checks for edge case: no path between selected nodes
//

#include <gtest/gtest.h>
#include "graph.h"
#include <climits>
namespace
{
    // Declaration of Fixture --> adjacency matrix creation and releasing
    class GraphTest : public ::testing::Test
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

    TEST_F(GraphTest, Matrix1Test)
    {
        adjacency_matrix = new int*[node_number];
        adjacency_matrix[0] = new int[node_number]{0,2,1,4};
        adjacency_matrix[1] = new int[node_number]{2,0,1,0};
        adjacency_matrix[2] = new int[node_number]{1,1,0,2};
        adjacency_matrix[3] = new int[node_number]{4,0,2,0};

        graph graph_sample{adjacency_matrix, node_number};
        dijkstra_outcome = graph_sample.lazy_dijkstra(1, 0);
        EXPECT_EQ(2, dijkstra_outcome.second);
        std::vector<int> outcome_vect{1,0};
        EXPECT_EQ(outcome_vect, dijkstra_outcome.first);

        dijkstra_outcome = graph_sample.lazy_dijkstra(3, 0);
        EXPECT_EQ(3, dijkstra_outcome.second);
        outcome_vect = {3,2,0};
        EXPECT_EQ(outcome_vect, dijkstra_outcome.first);
    }

    TEST_F(GraphTest, Matrix2Test)
    {
        adjacency_matrix = new int*[node_number];
        adjacency_matrix[0] = new int[node_number]{0,2,1,4};
        adjacency_matrix[1] = new int[node_number]{2,0,1,0};
        adjacency_matrix[2] = new int[node_number]{1,1,0,2};
        adjacency_matrix[3] = new int[node_number]{0,0,0,0};

        graph graph_sample{adjacency_matrix, node_number};
        dijkstra_outcome = graph_sample.lazy_dijkstra(3,1);
        EXPECT_EQ(INT_MAX, dijkstra_outcome.second);
        std::vector<int> outcome_vect{1};
        EXPECT_EQ(outcome_vect, dijkstra_outcome.first);
    }
}
