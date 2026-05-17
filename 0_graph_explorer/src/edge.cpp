//
// Edge source file
//

#include "../include/edge.h"

edge::edge(const int& weight, const int& node_id)
{
    this->node_id = node_id;
    this->weight = weight;
}