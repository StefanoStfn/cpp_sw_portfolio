# NumToy

NumToy is a small multidimensional array library implemented in C++ and exposed to Python through `pybind11`.

The project is intentionally minimal. It is not a NumPy replacement. Its purpose is to implement the core mechanics behind an N-dimensional numerical container: contiguous storage, shape-aware indexing, elementwise operations, transposition, and Python bindings.

## Features

- N-dimensional array container backed by contiguous C++ storage
- Row-major multidimensional indexing
- Elementwise arithmetic:
  - addition
  - subtraction
  - multiplication
  - division
- Scalar <--> array arithmetic, both directions are supported
- Unary negation
- Factory functions:
  - `zeros` tensor
  - `ones` tensor
  - `rand` tensor
- Generic N-dimensional transpose by axis reversal
- Flattened buffer export
- Python bindings through `pybind11`
- Readable `NToyArray(..., dtype=double)` representation
- `shape` representation

## Installation

From the project root:

```bash
pip install -e .
```

This builds the C++ extension module locally and installs NumToy in editable mode.

## Quick Start

```python
import numtoy as nt

print(f"Version: {nt.version()}")

a = nt.NToyArray(shape=(2, 4))
b = nt.ones(shape=(2, 4))

c = a + b

print(c)
print(c.flatten())
print(c.shape())
```

Example output:

```text
Version: 1.0.0
NToyArray([[1.000000,2.000000,3.000000,4.000000],[5.000000,6.000000,7.000000,8.000000]], dtype=double)
[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0]
(2, 4)
```

## Creating Arrays

### Default constructor

```python
a = nt.NToyArray(shape=(2, 3))
```

The default constructor initializes the internal buffer with sequential values.

### Constructor with data

```python
a = nt.NToyArray(
    shape=(2, 3),
    data=[1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
)
```

Data must be provided as a flattened row-major buffer. The data length must match the product of the shape dimensions.

### Zeros

```python
zero_tensor = nt.zeros(shape=(3, 3))
```

### Ones

```python
ones_tensor = nt.ones(shape=(3, 3))
```

### Random values

```python
rand_tensor = nt.rand(shape=(2, 4), min=-15.0, max=24.0)
```

`rand` generates uniformly distributed floating-point values in the requested range.

## Indexing

NumToy supports multidimensional indexing from Python:

```python
a = nt.NToyArray(shape=(2, 4))

print(a[0, 0])
print(a[1, 3])

a[1, 3] = 99.0
print(a[1, 3])
```

Internally, multidimensional indices are mapped into a flat contiguous buffer using row-major strides.

## Arithmetic

NumToy supports elementwise operations between arrays of the same shape:

```python
a = nt.NToyArray(shape=(2, 4))
b = nt.NToyArray(shape=(2, 4))

print(a + b)
print(a - b)
print(a * b)
print(a / b)
```

Scalar operations are also supported:

```python
a = nt.NToyArray(shape=(2, 4))

print(a + 10.0)
print(10.0 + a)

print(a - 10.0)
print(10.0 - a)

print(a * 2.0)
print(2.0 * a)

print(a / 2.0)
print(2.0 / a)
```

Unary negation is supported:

```python
print(-a)
```

## Transpose

`transpose` reverses the axes of an N-dimensional array.

```python
a = nt.NToyArray(shape=(2, 3, 4))
t = nt.transpose(a)

print(a.shape())
print(t.shape())
print(t)
```

Shape transformation:

```text
(2, 3, 4) -> (4, 3, 2)
```

For 1D arrays, transpose leaves the shape unchanged.

## Flatten

```python
a = nt.NToyArray(shape=(2, 4))

buffer = a.flatten()
print(buffer)
```

`flatten()` returns the internal row-major buffer as a Python list.

## API Reference

### Module functions

```python
nt.version() -> str
```

Returns the library version.

```python
nt.zeros(shape) -> NToyArray
```

Creates an array filled with zeros.

```python
nt.ones(shape) -> NToyArray
```

Creates an array filled with ones.

```python
nt.rand(shape, min, max) -> NToyArray
```

Creates an array filled with uniformly distributed random values.

```python
nt.transpose(array) -> NToyArray
```

Returns a new array with reversed axes.

### Class: `NToyArray`

```python
nt.NToyArray(shape)
nt.NToyArray(shape, data)
```

Creates a multidimensional array.

Methods:

```python
array.shape() -> str
array.flatten() -> list[float]
```

Operators:

```python
array + array
array - array
array * array
array / array

array + scalar
array - scalar
array * scalar
array / scalar

scalar + array
scalar - array
scalar * array
scalar / array

-array
```

Indexing:

```python
array[i, j, k]
array[i, j, k] = value
```

## Design Notes

NumToy is built around three core ideas:

```text
shape + flat buffer + index mapping
```

An N-dimensional array is represented as:

- a shape vector
- a contiguous one-dimensional buffer
- a row-major indexing scheme that maps N-dimensional indices into flat buffer offsets

This mirrors the core conceptual model used by real numerical array libraries, while keeping the implementation intentionally small.

## Limitations

NumToy intentionally does not implement:

- dtype polymorphism
- slicing
- views
- tesnor multiplication
- tensor contractions
- NumPy interoperability
- GPU support

These are out of scope for version 1.0.

## Development

C++ tests are implemented with GoogleTest.

Python binding tests can be run with:

```bash
python -m unittest discover python_tests
```

## License

MIT License.
