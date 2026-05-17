# Graph Explorer

C++ graph exploration with shortest-path-scanner project focused on:

* scalable graph data structures
* adjacency matrix to adjacency list conversion
* Lazy Dijkstra shortest-path algorithm
* Unit testing with GoogleTest
* Benchmarking and Runtime Profiling

---

## Project Structure

```text
0_graph_explorer/
├── CMakeLists.txt
├── include/
│   ├── edge.h
│   ├── graph.h
│   └── node.h
├── src/
│   ├── edge.cpp
│   ├── graph.cpp
│   ├── main.cpp
│   └── node.cpp
├── tests/
│   ├── test_edge.cpp
│   ├── test_graph.cpp
│   └── test_node.cpp
└── images/
    └── exec_time_benchmark.png
```

---

## Features

### Graph Representation

The graph is initially generated as a weighted adjacency matrix and internally converted into an adjacency-list representation.

#### Sparse Graph Support

Zero or negative weights are ignored during node construction:

* `0` represents no connection
* negative weights are discarded
* only positive-weight edges are stored

This is done for creating an undirected weighted graph.

---

## Lazy Dijkstra Algorithm

The project implements a lazy version of Dijkstra's shortest-path algorithm using:

* adjacency lists
* `std::priority_queue`
* min-heap ordering via `std::greater<>`

The algorithm returns:

* shortest-path distance
* reconstructed shortest path

---

## Unit Testing

Testing is implemented with GoogleTest.

Covered components:

### Edge

* constructor correctness
* getter correctness
* vector storage compatibility

### Node

* empty neighbor handling
* sparse graph behavior
* zero-weight edge skipping
* negative-weight skipping
* adjacency construction validation

### Graph

* shortest path correctness
* disconnected graph handling
* path reconstruction
* distance validation

---

# Benchmarking

The project includes runtime profiling experiments for Dijkstra's algorithm.

Benchmarking currently explores:

* runtime scaling
* heap ordering effects
* average execution time across multiple randomized graphs

The runtime is measured using:

```cpp
std::chrono::high_resolution_clock
```

and averaged over multiple independent runs.  
Here below the results:
![Benchmark Plot](./images/exec_time_benchmark.png)

## Current Observations

* Incorrect max-heap ordering drastically worsens performance.
    ```text
    O(V²)
    ```
* Proper min-heap ordering restores expected Dijkstra behavior.
    ```text
    O(E log V)
    ```
---

# Learning Goals

This project is intended as both:

* a graph-algorithm implementation project
* a systems-programming and modern C++ learning project

with focus on:

* algorithmic complexity
* memory ownership
* RAII
* testing
* profiling
