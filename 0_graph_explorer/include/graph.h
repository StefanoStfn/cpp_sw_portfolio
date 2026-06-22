//
// Graph Header, builds the graph and exposes only lazy dijkstra
//
#ifndef GRAPH_H
#define GRAPH_H

#pragma once

#include "node.h"
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>

class graph
{
    public:
        graph(int** adjacency_matrix, const int& node_number);
        std::pair<std::vector<int>, int> lazy_dijkstra(
            const int& start_node,
            const int& end_node
        ) const;

    private:
        const std::vector<edge>& get_neighbours(const int& node_index) const;
        int node_number;
        ///Interface to nodes
        std::vector<node> nodes_vect;
};

#endif // GRAPH_H
