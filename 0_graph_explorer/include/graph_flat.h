//
// Graph Header, builds the graph and exposes only lazy dijkstra. Implemented with Flat Memory
//

#ifndef GRAPH_EXPLORER_GRAPH_FLAT_H
#define GRAPH_EXPLORER_GRAPH_FLAT_H

#include <vector>
#include <climits>
#include <queue>
#include <algorithm>

class GraphFlat
{
    public:
        GraphFlat(int** adjacency_matrix, const int& node_number);
        std::pair<std::vector<int>, int> lazy_dijkstra(
            const int& start_node,
            const int& end_node
        ) const;
        const std::vector<int>& get_edge_targets() const {return edge_targets;}
        const std::vector<int>& get_edge_weights() const {return edge_weights;}
        const std::vector<int>& get_offsets() const {return offsets;}

    private:
        int node_number;
        std::vector<int> edge_targets;
        std::vector<int> edge_weights;
        std::vector<int> offsets;
};


#endif //GRAPH_EXPLORER_GRAPH_FLAT_H
