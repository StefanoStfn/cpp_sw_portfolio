//
// This Main is glue logic for using the Graph structure,
// dynamically create the adjacency matrix and store it in a file
//

#include <iostream>
#include <fstream>
#include <random>
#include <memory>
#include <ctime>
#include <chrono>
#include "../include/graph.h"

using namespace std;

int** generate_weighted_graph(
    const int node_number
);

void print_graph_on_file(
    int** adjacency_matrix,
    const int node_number
);

int main(const int argc, char *argv[])
{
    /// Variables
    string workflow;
    int node_number;
    unique_ptr<graph> weighted_graph;
    int start_node;
    int end_node;
    int counter = 0;
    int iterations = 50;
    vector<double> execution_times;
    /// Checking
    vector<int> nodes{
        10,20,30,40,50,60,70,80,90,100,
        200,300,400,500,600,700,800,900,
        1000,2000,3000,4000,5000};
    vector<int>::iterator n_number_it;
    for (n_number_it=nodes.begin(); n_number_it!=nodes.end(); n_number_it++)
    {
        cout << "Node Number " << *n_number_it << " in progress..." <<endl;
        execution_times.push_back(0.0);
        for (int i=0; i<iterations; i++)
        {
            node_number = *n_number_it;
            start_node = 0;
            end_node = node_number-5;
            int **adjacency_matrix = nullptr;
            /// Randomize Graph
            adjacency_matrix = generate_weighted_graph(
                node_number
            );
            // Creation of the Weighted Graph using the Graph class
            weighted_graph = make_unique<graph>(
                adjacency_matrix,
                node_number
            );
            auto start = std::chrono::high_resolution_clock::now();
            // run Dijkstra Algorithm
            weighted_graph->lazy_dijkstra(
                start_node,
                end_node
            );
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            execution_times[counter] += duration.count()/static_cast<double>(iterations);
            for(int v = 0; v < node_number; v++)
            {
                delete[] adjacency_matrix[v];
            }
            delete[] adjacency_matrix;
        }
        counter++;
    }

    for (int i=0; i<nodes.size(); i++)
    {
        cout << "Node Number: " << nodes[i] << endl;
        cout << "    " << "Average run time: " << execution_times[i] << " us" << endl;
    }
    for (int i=0; i<nodes.size(); i++)
    {
        cout << nodes[i] << ',' << endl;
    }
    for (int i=0; i<nodes.size(); i++)
    {
        cout << execution_times[i] << ',' << endl;
    }
    return 0;
}


int** generate_weighted_graph(const int node_number)
{
    /// This function creates a ranom undirectional weighted graph
    /// Variable definitions
    int** adjacency_matrix = new int* [node_number];
    int tmp_weight;
    int current_roll;
    mt19937 generator(time(nullptr));
    // Generate Random number between 0 and 20
    uniform_int_distribution<int> distribution(0,20);
    // This below is used to randomly make the matrix more sparse
    // I'll use 15/21 probability to put the values as 0
    uniform_int_distribution<int> dice_roll (1,21);

    for(int i=0; i<node_number; i++)
    {
        adjacency_matrix[i] = new int[node_number];
    }
    for(int i=0; i<node_number; i++)
    {
        for(int j=0; j<node_number; j++)
        {
            if(j < i)
            {
                tmp_weight = distribution(generator);
                current_roll = dice_roll(generator);
                // 15/21 probability
                if (current_roll <= 15)
                {
                    adjacency_matrix[i][j] = 0;
                    adjacency_matrix[j][i] = 0;
                }
                else
                {
                    adjacency_matrix[i][j] = tmp_weight;
                    adjacency_matrix[j][i] = tmp_weight;
                }
            }
            else
            {
                adjacency_matrix[i][j] = 0;
            }
        }
    }
    return adjacency_matrix;
}


void print_graph_on_file(int** adjacency_matrix, const int node_number)
{
    // This function dump the matrix output in a csv file
    //
    ofstream OutFile("data/adjacency_matrix.csv", ios::out);
    /// Write Header
    OutFile << ',';
    for(int i=0; i<node_number; i++)
    {
        if(i != node_number-1)
        {
            OutFile << 'N' << i << ',';
        }
        else
        {
            OutFile << 'N' << i << endl;
        }
    }
    /// Write Values
    for(int i=0; i<node_number; i++)
    {
        OutFile << 'N' << i << ',';
        for(int j=0; j<node_number; j++)
        {
            if(j != node_number-1)
            {
                OutFile << adjacency_matrix[i][j] << ',';
            }
            else
            {
                OutFile << adjacency_matrix[i][j] << endl;
            }
        }
    }
    // Close the file
    OutFile.close();
}
