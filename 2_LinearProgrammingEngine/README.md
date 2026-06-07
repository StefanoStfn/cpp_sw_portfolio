# Linear Programming Engine

C++ Linear Programming engine with Python bindings.

This project implements a continuous Linear Programming solver using the Simplex algorithm with Big-M support. The backend is written in C++ and exposed to Python through `pybind11`, allowing LP models to be written with a compact algebraic API, using an algebraic Domain Specific Language (DSL).

## Features

- C++ Simplex backend
- Python bindings with `pybind11`
- Algebraic Python modeling syntax
- Maximization and minimization
- Support for `<=`, `>=`, and `==` constraints
- Big-M artificial variable handling
- Detection of:
  - optimal solutions
  - infeasible problems
  - unbounded problems
  - degenerate solutions
  - alternative optimal solutions
- Configurable:
  - simplex pivot strategy
  - epsilon tolerance
  - Big-M value
  - maximum iterations

## Example

```python
import lpengine as lp

solver = lp.LPSolver()

x = solver.add_variable("x")
y = solver.add_variable("y")

solver.add_constraint(2*x + y <= 10)
solver.add_constraint(x + y <= 7)
solver.add_constraint(x + 2*y <= 12)

solver.objective_function(
    30*x + 40*y,
    lp.Maximize
)

solver.run()

print(f"Status: {solver.get_status()}")
print(f"Objective value: {solver.get_solution_rhs()}")
print(f"Variable Values: {solver.get_variable_values()}")
```

Expected result:

```text
Status: SolveStatus.Optimal
Objective value: 260.0
Variable Values: {'s0': 1.0, 's1': 0.0, 's2': 0.0, 'x': 2.0, 'y': 5.0}
```

## Python API

### Create a solver

```python
solver = lp.LPSolver()
```

Optional configuration:

```python
solver = lp.LPSolver(
    strategy=lp.Simplex,
    solver_strategy=lp.BlandRule,
    epsilon=1e-9,
    bigM=1e6,
    max_iterations=4000
)
```

### Add variables

```python
x = solver.add_variable("x")
y = solver.add_variable("y")
```

### Add constraints

```python
solver.add_constraint(x + y <= 10)
solver.add_constraint(x - y >= 2)
solver.add_constraint(x + 2*y == 7)
```

### Add objective

```python
solver.objective_function(3*x + 2*y, lp.Maximize)
solver.objective_function(3*x + 2*y, lp.Minimize)
```

### Read results

```python
status = solver.get_status()
objective_value = solver.get_solution_rhs()
values = solver.get_variable_values()

is_degenerate = solver.is_degenerate()
has_alternative_solution = solver.is_alternative_sol()
```

## Solver Status

Available status values:

```python
SolveStatus.NotStarted
SolveStatus.Optimal
SolveStatus.Infeasible
SolveStatus.Unbounded
SolveStatus.IterationLimitReached
```

Shortcut aliases are also exposed:

```python
lp.Optimal
lp.Infeasible
lp.Unbounded
```

## Build and Install

From the project root:

```bash
pip install -e .
```

The package uses:

- CMake
- `scikit-build-core`
- `pybind11`

## CMake Build

Build manually with tests enabled:

```bash
cmake -S . -B build -DLP_ENGINE_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build
```

Build without tests:

```bash
cmake -S . -B build -DLP_ENGINE_BUILD_TESTS=OFF
cmake --build build
```

## Testing

The project includes C++ unit and system tests using GoogleTest.

The test suite covers:

- frontend expression compilation
- tableau construction
- simplex pivot mechanics
- feasible optimal problems
- minimization
- Big-M artificial variables
- infeasible problems
- unbounded problems
- degenerate solutions
- alternative optimal solutions

## Python Interface Tests

A small Python `unittest` suite validates the public binding layer. These tests are intentionally lightweight: the C++ test suite verifies the solver internals, while the Python tests check that the installed module can be imported, the algebraic DSL works, enum aliases are exposed correctly, and results can be read through the public API.

Covered Python cases:

- classic feasible maximization
- minimization with Big-M
- unbounded problem detection
- infeasible problem detection

Run with:

```bash
python -m unittest tests/test_python_interface.py
```

## Current Scope

Supported:

```text
continuous LP
x >= 0
max / min
<= / >= / ==
Simplex
Big-M
```

Not currently supported:

```text
integer programming
free variables
explicit variable bounds other than x >= 0
```

## Project Structure

```text
## Project Structure

```text
2_LinearProgrammingEngine/
├── include/
│   ├── common/
│   ├── interface/
│   ├── modeling/
│   └── simplex/
├── src/
│   ├── interface/
│   ├── modeling/
│   └── simplex/
├── tests/
│   ├── fixtures/
│   ├── system_test.cpp
│   ├── test_lp_frontend.cpp
│   ├── test_relation_expression_operators.cpp
│   ├── test_simplex_maincore.cpp
│   └── test_tableau.cpp
├── python/
│   ├── python_tests/
│   └── lpengine.pyi
├── CMakeLists.txt
├── LICENSE
├── pyproject.toml
└── README.md
```

## Version

```python
import lpengine as lp

print(lp.version())
```

## Notes

This is V1 of the LP Engine. The current backend focuses on a complete Simplex + Big-M implementation for continuous linear programs.
