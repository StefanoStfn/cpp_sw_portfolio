//
// Created by Martina on 18/05/2026.
//

#ifndef INC_1_NUMTOY_NUMTOY_LIB_H
#define INC_1_NUMTOY_NUMTOY_LIB_H

#pragma once
#include "./ntoyarray.h"

namespace numtoy
{
    // Symmetric Operator
    NToyArray operator+ (double b, const NToyArray& b_array);
    NToyArray operator* (double b, const NToyArray& b_array);
    // Non-symmetric Operator
    NToyArray operator- (double b, const NToyArray& b_array);
    NToyArray operator/ (double b, const NToyArray& b_array);
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

}

#endif //INC_1_NUMTOY_NUMTOY_LIB_H
