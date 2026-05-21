// operator+(scalar, array): Implements left-side scalar addition broadcasting.
// operator*(scalar, array): Implements left-side scalar multiplication broadcasting.
// operator-(scalar, array): Implements left-side scalar subtraction broadcasting.
// operator/(scalar, array): Implements left-side scalar division broadcasting.
// operator<<(ostream, array): Implements the string output formatting for the array content.
// zeros: Creates an N-dimensional array initialized with zeros.
// ones: Creates an N-dimensional array initialized with ones.
// rand: Creates an N-dimensional array initialized with uniformly distributed random values.

#ifndef INC_1_NUMTOY_NUMTOY_LIB_H
#define INC_1_NUMTOY_NUMTOY_LIB_H

#pragma once
#include <sstream>
#include "./ntoyarray.h"

namespace numtoy
{
    // Symmetric Operator
    NToyArray operator+ (double b, const NToyArray& b_array);
    NToyArray operator* (double b, const NToyArray& b_array);
    // Non-symmetric Operator
    NToyArray operator- (double b, const NToyArray& b_array);
    NToyArray operator/ (double b, const NToyArray& b_array);
    // StdOut operator
    std::ostream& operator<< (std::ostream& os, const NToyArray& array);
    // Custom Matrix
    NToyArray zeros (std::vector<std::size_t> shape);
    NToyArray ones (std::vector<std::size_t> shape);
    NToyArray rand (
        std::vector<std::size_t> shape,
        double min = 0.0,
        double max = 1.0
    );
    // Transpose operation
    NToyArray transpose (const NToyArray& array);
    inline std::string version() {return "1.0.0";};
}

#endif //INC_1_NUMTOY_NUMTOY_LIB_H
