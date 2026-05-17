//
// Graph implementation, implement constructor, neighbors getter and dijkstra
//

#include "../include/graph.h"
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

graph::graph(int** adjacency_matrix, const int node_number)
{
    for (int i = 0; i < node_number; i++)
    {
        this->nodes_vect.push_back(
            node(adjacency_matrix[i], i, node_number)
        );
    }
    this->node_number = node_number;
}

std::vector<edge> graph::get_neighbours(const int node_index)
{
    return this->nodes_vect[node_index].get_edge_vect();
}


std::pair<std::vector<int>, int> graph::lazy_dijkstra(
    const int start_node,
    const int end_node
)
{
    // all initialized to the highest int value of the machine
    std::vector<int> dist_vect (node_number, INT_MAX) ;
    std::vector<int> path_vect (node_number, -1) ;
    std::pair<std::vector<int>, int> output_tuple;
    std::vector<int> reconstructed_path;
    using queue_item = std::pair<int, int>;
    // first  = distance
    // second = node id
    std::priority_queue<
        queue_item,
        std::vector<queue_item>,
        std::greater<queue_item>
    > pq_id_dist;
    std::vector<edge> n_vect;
    std::vector<edge>::iterator n_it;
    int new_dist;
    int index;
    int n_index;
    int min_dist;
    int current_node = end_node;
    // Dijkstra Starts here
    dist_vect[start_node] = 0 ;
    pq_id_dist.emplace(
        dist_vect[start_node], start_node
    );
    while (pq_id_dist.size() != 0)
    {
        index = pq_id_dist.top().second;
        min_dist = pq_id_dist.top().first;
        pq_id_dist.pop();
        n_vect = get_neighbours(index);
        if (dist_vect[index] >= min_dist)
        {
            for (n_it = n_vect.begin(); n_it != n_vect.end(); n_it++)
            {
                n_index = n_it->get_node_id();
                new_dist = dist_vect[index] + n_it->get_weight();
                if (new_dist < dist_vect[n_index])
                {
                    path_vect[n_index] = index;
                    dist_vect[n_index] = new_dist;
                    pq_id_dist.emplace(new_dist, n_index);
                }
            }
        }
    }
    // Build back the path
    while (current_node != -1)
    {
        reconstructed_path.push_back(current_node);
        current_node = path_vect[current_node];
    }
    std::reverse(
        reconstructed_path.begin(),
        reconstructed_path.end()
    );
    // building the output to be returned
    output_tuple.first = reconstructed_path;
    output_tuple.second = dist_vect[end_node];
    return output_tuple;
}