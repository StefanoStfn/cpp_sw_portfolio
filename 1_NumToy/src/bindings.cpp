/*
 * Binding Interface for NumToy Library
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "../include/numtoy_lib.h"

namespace py = pybind11;


PYBIND11_MODULE(numtoy, m, py::mod_gil_not_used())
{
    // Lib Methods
    m.doc() = "The version of the library"; // optional module docstring
    m.def("version", &numtoy::version, "The Library Version");
    m.def(
        "zeros",
        &numtoy::zeros,
        py::arg("shape"),
        "MultiDimArray of Zeros"
    );

    m.def(
        "ones",
        &numtoy::ones,
        py::arg("shape"),
        "MultiDimArray of Ones"
    );

    m.def(
        "rand",
        &numtoy::rand,
        py::arg("shape"),
        py::arg("min"),
        py::arg("max"),
        "MultiDimArray of Uniform Rand Number"
    );

    m.def(
        "transpose",
        &numtoy::transpose,
        py::arg("array"),
        "Perform the Transpose operation"
    );

    // NToyArray Class
    py::class_<numtoy::NToyArray>(m, "NToyArray")
        // First Constructor
        .def(
            py::init<std::vector<std::size_t>>(),
            py::arg("shape")
        )
        // Constructor Overload
        .def(
            py::init<std::vector<std::size_t>, std::vector<double>>(),
            py::arg("shape"),py::arg("data")
        )
        // Shape Method
        .def("shape", &numtoy::NToyArray::shape_string)
        // Flatten
        .def("flatten", &numtoy::NToyArray::get_buffer)
        // Math Operators
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * py::self)
        .def(py::self / py::self)
        .def(double() + py::self)
        .def(double() - py::self)
        .def(double() * py::self)
        .def(double() / py::self)
        .def(py::self + double())
        .def(py::self - double())
        .def(py::self * double())
        .def(py::self / double())
        .def("__repr__", &numtoy::NToyArray::to_string)
        .def("__getitem__",
            [](numtoy::NToyArray& arr, const std::vector<std::size_t>& indices) -> double {return arr(indices);})
         .def("__setitem__",
             [](numtoy::NToyArray& arr, const std::vector<std::size_t>& indices, double value) {arr(indices) = value;});
}
