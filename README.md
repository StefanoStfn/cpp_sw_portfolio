# C++ SW Portfolio Readme

## Motivations

I got in touch with C++ in my second year of my Bachelor's Degree.  
At that time, I got a rough experience because after having spent 2 months in a big project for graph loop detection using linked lists, I got an unfair mark.
I remember I had only 3 hours of sleeping time the night before the presentation, because I was completing the project and lately I also discovered my professor's assistant didn't read my code at all.   
So I have to admit, the mark was strongly biased by me not being able to focus and communicate efficiently, even though the software was working correctly.

At that time I learned a few lessons:  
* Great subjects and miserable experiences bring to bad memories in general
* Sleeping well before a presentation, is strongly recommended
* I needed to fix my trauma with C++, one day..


So here we are, after some years...  
This portfolio acts as a strategy of mine to fill gaps and fix bad experiences.  
It is used to revisit mid/low level programming techniques, apply modern C++ software design and algorithmic reasoning that I use every day in Python-based workflows at work, even though I am a Digital Physical Implementation Engineer.
Ultimately, this portfolio is meant to help me grow into a more complete software engineer, capable of building production-ready C++ software.

Then, below there is the list of C++ projects that compose this portfolio.  

# Projects Recap

```md
## 0 Graph Explorer

C++ graph exploration with shortest-path scanner project.

### Structure

0_graph_explorer/
├── include/  
├── src/  
├── tests/  
├── images/  
├── CMakeLists.txt  
└── README.md  


### Folder Purpose

* `include/` → graph, node and edge interfaces
* `src/` → graph generation and cpp source files
* `tests/` → GoogleTest validation suite
* `images/` → benchmark plot and runtime visualization

### Highlights

* Lazy Dijkstra implementation using `std::priority_queue`
* Benchmark comparison between max-heap and min-heap behavior
* Runtime and memory observations on sparse random graphs

```
---  

```md

## 1 NumToy

C++ multidimensional array (Tensor) library with Python bindings.

### Structure

1_NumToy/
├── include/  
├── src/  
├── tests/  
├── python_tests/  
├── CMakeLists.txt  
├── pyproject.toml  
├── LICENSE  
└── README.md  

### Folder Purpose

* `include/` → NToyArray interface and NumToy public API declarations
* `src/` → C++ array implementation, library functions and pybind11 bindings
* `tests/` → GoogleTest validation suite for the C++ core
* `python_tests/` → Python unittest suite for the exposed Python API
* `pyproject.toml` → pip/scikit-build-core packaging configuration

### Highlights

* N-dimensional dense array backed by a contiguous row-major `std::vector<double>` buffer
* Runtime shape handling, stride-based indexing and multidimensional element access
* Elementwise arithmetic operators with scalar-array support in both directions
* Factory functions for `zeros`, `ones` and uniformly distributed random arrays `rand`
* Generic N-dimensional transpose through recursive index traversal and axis reversal
* Python bindings with pybind11 exposing constructors, operators, indexing, flattening and representation
* Pip-installable package using CMake and scikit-build-core
```
---  

```md
## 2 Linear Programming Engine

C++ Linear Programming Engine solver with Python bindings and interface definition.

### Structure

2_LinearProgrammingEngine/  
├── include/  
├── src/  
├── tests/ 
├── python/  
├── CMakeLists.txt  
├── pyproject.toml  
├── LICENSE  
└── README.md  

### Folder Purpose

* `include/` → solver interface, modeling API, enums and simplex/tableau declarations
* `src/` → C++ implementation, Simplex core, Big-M tableau builder and pybind11 bindings
* `tests/` → GoogleTest validation suite for the C++ backend and system behavior
* `python/` → Python stub file for autocomplete and type hints and tests
* `pyproject.toml` → pip/scikit-build-core packaging configuration

### Highlights

* Continuous Linear Programming engine for non-negative decision variables
* Simplex backend with Bland Rule and Most Negative pivot strategies
* Big-M support for `>=` and `==` constraints through artificial variables
* Support for maximization and minimization problems
* Detection of optimal, infeasible, unbounded, degenerate and alternative-optimum cases
* Algebraic Python DSL for expressions such as `2*x + y <= 10`
* Python bindings with pybind11 exposing solver API, enums, operators and result accessors
* Python `.pyi` interface file for autocomplete and type hints
* Pip-installable package using CMake and scikit-build-core

```
---  