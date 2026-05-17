//
// Node source file --> only constructor, discard zero-negative weights
//

#include "../include/node.h"

node::node(
    const int* connection_array,
    const int id,
    const int node_number
)
{
    this->id = id;
    for (int i = 0; i < node_number; i++)
    {
        if (connection_array[i] > 0 )
        {
            this->edge_vect.emplace_back(
                connection_array[i], i
            );
        }
    }
}