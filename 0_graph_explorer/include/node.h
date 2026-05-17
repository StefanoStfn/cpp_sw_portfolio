//
// Node header for storing neighbors and check for invalid weights
//

#ifndef GRAPH_EXPLORER_NODE_H
#define GRAPH_EXPLORER_NODE_H
#include "edge.h"
#include <vector>

class node
{
    public:
        node(
            const int* connection_array,
            int id,
            const int node_number
        );
        int get_id() const {return id; };
        std::vector<edge> get_edge_vect() const {return edge_vect; };

    private:
        std::vector<edge> edge_vect;
        int id;
};

#endif //GRAPH_EXPLORER_NODE_H
