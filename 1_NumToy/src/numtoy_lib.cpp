//
// Created by Martina on 18/05/2026.
//

#include "../include/numtoy_lib.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>

namespace numtoy
{
    numtoy::NToyArray operator+ (double a, const numtoy::NToyArray& b_array)
    {
        return b_array + a;
    }
    numtoy::NToyArray operator* (double a, const numtoy::NToyArray& b_array)
    {
        return b_array * a;
    }
    numtoy::NToyArray operator- (double a, const numtoy::NToyArray& b_array)
    {
        /*
         * get the buffer, modify it element-wise and overwrite the buffer
         * in the array class directly
         */
        std::vector<std::size_t> b_shape = b_array.shape();
        numtoy::NToyArray new_array(b_array.shape());
        std::vector<double> b_buffer = b_array.get_buffer();
        std::transform(
            b_buffer.begin(),
            b_buffer.end(),
            b_buffer.begin(),
            [a](double y){return a-y;}
        );
        new_array.set_buffer(b_buffer);
        return new_array;
    }

    numtoy::NToyArray operator/ (double a, const numtoy::NToyArray& b_array)
    {
        /*
        * get the buffer, modify it element-wise and overwrite the buffer
        * in the array class directly
        */
        std::vector<std::size_t> b_shape = b_array.shape();
        numtoy::NToyArray new_array(b_array.shape());
        std::vector<double> b_buffer = b_array.get_buffer();
        std::transform(
            b_buffer.begin(),
            b_buffer.end(),
            b_buffer.begin(),
            [a](double y){return a/y;}
        );
        new_array.set_buffer(b_buffer);
        return new_array;
    }

    // Custom initialization Matrices

    numtoy::NToyArray zeros (std::vector<std::size_t> shape)
    {
        numtoy::NToyArray new_array(shape);
        std::size_t tmp_buffer_size = new_array.get_buffer().size();
        new_array.set_buffer(
            std::vector<double>(tmp_buffer_size, 0)
        );
        return new_array;
    }

    numtoy::NToyArray ones (std::vector<std::size_t> shape)
    {
        numtoy::NToyArray new_array(shape);
        std::size_t tmp_buffer_size = new_array.get_buffer().size();
        new_array.set_buffer(
            std::vector<double>(tmp_buffer_size, 1)
        );
        return new_array;
    }

    numtoy::NToyArray rand (std::vector<std::size_t> shape, double min, double max)
    {
        if (max < min)
        {
            throw std::invalid_argument("max must be greater than min.");
        }
        numtoy::NToyArray new_array(shape);
        // from cplusplus reference
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(min, max);
        std::size_t tmp_buffer_size = new_array.get_buffer().size();
        std::vector<double> buffer(tmp_buffer_size);
        std::transform(
            buffer.begin(),
            buffer.end(),
            buffer.begin(),
            [&dis, &gen](double a){ return dis(gen);}
        );
        new_array.set_buffer(buffer);
        return new_array;
    }
}
