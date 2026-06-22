//
// Created by Martina on 22/06/2026.
//

#include "../include/graph_flat.h"


GraphFlat::GraphFlat(int** adjacency_matrix, const int& node_number)
{
    this->node_number = node_number;
    offsets.push_back(0);
    for (int i = 0; i < node_number; i++)
    {
        offsets.push_back(0);
        for (int j = 0; j < node_number; j++)
        {
            if (adjacency_matrix[i][j] > 0)
            {
                edge_targets.push_back(j);
                edge_weights.push_back(adjacency_matrix[i][j]);
            }
        }
        offsets[i+1] = edge_targets.size();
    }
}

std::pair<std::vector<int>, int> GraphFlat::lazy_dijkstra(
    const int& start_node,
    const int& end_node
) const
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
    int current_node = end_node;
    // Dijkstra Starts here
    dist_vect[start_node] = 0 ;
    pq_id_dist.emplace(
        dist_vect[start_node], start_node
    );
    while (!pq_id_dist.empty())
    {
        const int index = pq_id_dist.top().second;
        const int min_dist = pq_id_dist.top().first;
        pq_id_dist.pop();
        // new logic
        if (dist_vect[index] >= min_dist)
        {
            const int start_id = offsets[index];
            const int end_id = offsets[index+1];
            for (int i = start_id; i < end_id; ++i)
            {
                int n_index = edge_targets[i];
                int new_dist = dist_vect[index] + edge_weights[i];
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