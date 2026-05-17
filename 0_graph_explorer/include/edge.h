//
// Edge header for edge id and weight storing
//

#ifndef GRAPH_EXPLORER_EDGE_H
#define GRAPH_EXPLORER_EDGE_H


class edge
{
    public:
        edge(const int& weight, const int& node_id);
        int get_weight() const {return weight;};
        int get_node_id() const {return node_id;};

    private:
        int weight;
        int node_id;
};

#endif //GRAPH_EXPLORER_EDGE_H
