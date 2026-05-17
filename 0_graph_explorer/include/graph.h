//
// Graph Header, builds the graph and exposes only lazy dijkstra
//
#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include <vector>

class graph
{
    public:
        graph(int** adjacency_matrix, const int node_number);
        std::pair<std::vector<int>, int> lazy_dijkstra(
            const int start_node,
            const int end_node
        );

    private:
        std::vector<edge> get_neighbours(const int node_index);
        int node_number;
        ///Interface to nodes
        std::vector<node> nodes_vect;
};

#endif // GRAPH_H
