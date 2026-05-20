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
    numtoy::NToyArray operator+ (double b, const numtoy::NToyArray& b_array);
    numtoy::NToyArray operator* (double b, const numtoy::NToyArray& b_array);
    // Non-symmetric Operator
    numtoy::NToyArray operator- (double b, const numtoy::NToyArray& b_array);
    numtoy::NToyArray operator/ (double b, const numtoy::NToyArray& b_array);
    // Custom Matrix
    numtoy::NToyArray zeros (std::vector<std::size_t> shape);
    numtoy::NToyArray ones (std::vector<std::size_t> shape);
    numtoy::NToyArray rand (std::vector<std::size_t> shape, double min = 0.0, double max = 1.0);
    // Transpose operation
    numtoy::NToyArray transpose (numtoy::NToyArray& array);

}

#endif //INC_1_NUMTOY_NUMTOY_LIB_H
