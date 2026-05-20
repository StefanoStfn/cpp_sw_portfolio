// operator+(scalar, array): Implements left-side scalar addition broadcasting.
// operator*(scalar, array): Implements left-side scalar multiplication broadcasting.
// operator-(scalar, array): Implements left-side scalar subtraction broadcasting.
// operator/(scalar, array): Implements left-side scalar division broadcasting.
// zeros: Creates an N-dimensional array initialized with zeros.
// ones: Creates an N-dimensional array initialized with ones.
// rand: Creates an N-dimensional array initialized with uniformly distributed random values.
// compute_index_: Maps multidimensional indices into contiguous row-major buffer offsets.
// recursive_transpose_: Recursively traverses multidimensional indices to rebuild the transposed buffer.
// transpose: Reverses array axes and reconstructs the transposed multidimensional buffer.

#include "../include/numtoy_lib.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>

namespace numtoy
{
    NToyArray operator+ (double a, const NToyArray& b_array)
    {
        return b_array + a;
    }
    NToyArray operator* (double a, const NToyArray& b_array)
    {
        return b_array * a;
    }
    NToyArray operator- (double a, const NToyArray& b_array)
    {
        /*
         * get the buffer, modify it element-wise and overwrite the buffer
         * in the array class directly
         */
        std::vector<std::size_t> b_shape = b_array.shape();
        NToyArray new_array(b_array.shape());
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

    NToyArray operator/ (double a, const NToyArray& b_array)
    {
        /*
        * get the buffer, modify it element-wise and overwrite the buffer
        * in the array class directly
        */
        std::vector<std::size_t> b_shape = b_array.shape();
        NToyArray new_array(b_array.shape());
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

    NToyArray zeros (std::vector<std::size_t> shape)
    {
        NToyArray new_array(shape);
        std::size_t tmp_buffer_size = new_array.get_buffer().size();
        new_array.set_buffer(
            std::vector<double>(tmp_buffer_size, 0)
        );
        return new_array;
    }

    NToyArray ones (std::vector<std::size_t> shape)
    {
        NToyArray new_array(shape);
        std::size_t tmp_buffer_size = new_array.get_buffer().size();
        new_array.set_buffer(
            std::vector<double>(tmp_buffer_size, 1)
        );
        return new_array;
    }

    NToyArray rand (std::vector<std::size_t> shape, double min, double max)
    {
        if (max < min)
        {
            throw std::invalid_argument("max must be greater than min.");
        }
        NToyArray new_array(shape);
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

    // General striding function for mapping multidim indices into an index
    std::size_t compute_index_ (
        const std::vector<std::size_t>& indices,
        std::vector<std::size_t> shape)
    {
        /*
         * Given an index vector, this multiplies the shape iteratively
         * and return an index for the buffer.
         * This same result can be obtained recursively too!
         */
        std::vector<std::size_t> stride_vector(shape.size(), 1);
        std::vector<std::size_t> tmp_multiply(shape.size());
        std::size_t out_index;
        // evaluate strides
        /*
         * k*stride0 + l*stride1 + ...
         * The for evaluates stride_ith
         * the transform combine the information
         */
        for (size_t i = 0; i < shape.size()-1; ++i)
        {

            stride_vector[i] = std::accumulate(
                shape.begin()+i+std::size_t{1},
                shape.end(),
                std::size_t{1},
                std::multiplies<std::size_t>()
            );
        }
        std::transform(
            stride_vector.begin(),
            stride_vector.end(),
            indices.begin(),
            tmp_multiply.begin(),
            [](std::size_t a, std::size_t b){return a*b;}
        );
        // accumulate to get a single index for the buffer
        out_index = std::accumulate(
            tmp_multiply.begin(),
            tmp_multiply.end(),
            std::size_t{0}
        );
        return out_index;
    }

    void recursive_transpose_ (
        std::vector<std::size_t>& shape,
        const std::vector<std::size_t>& old_shape,
        const std::vector<std::size_t>& new_shape,
        std::vector<std::size_t>& actual_index_array,
        const std::vector<double>& old_buffer,
        std::vector<double>& new_buffer,
        std::size_t depth)
    {
        if (depth == shape.size())
        {
            std::size_t old_index = compute_index_(actual_index_array, old_shape);
            // create and reverse the new index
            std::vector<std::size_t> new_index_array = actual_index_array;
            std::reverse(
                new_index_array.begin(), new_index_array.end()
            );
            std::size_t new_index = compute_index_(new_index_array, new_shape);
            new_buffer[new_index] = old_buffer[old_index];
        }
        else
        {
            std::size_t first_axis_dim = shape[depth];
            for (std::size_t i = 0; i < first_axis_dim; ++i)
            {
                actual_index_array.push_back(i);
                recursive_transpose_(
                    shape,
                    old_shape,
                    new_shape,
                    actual_index_array,
                    old_buffer,
                    new_buffer,
                    depth + 1
                );
                actual_index_array.pop_back();
            }
        }
    }

    NToyArray transpose (const NToyArray& array)
    {
        /*
         * Transpose operation reverse the axes of an NDimArray
         * (3,2) --> (2,3)
         * (3,2,4) --> (4,2,3)
         * So, the i,j,k element becomes the k,j,i one
         * Recursion / Iteration for this are both feasible
         */
        // vector to be popped
        std::vector<std::size_t> shape = array.shape();
        // permanent full reference to the old shape
        std::vector<std::size_t> full_old_shape = array.shape();
        // Depth tracking
        std::size_t depth = 0;
        // new array shape to be reversed --> basic transpose logic
        std::vector<std::size_t> new_shape = array.shape();
        // Dynamic index variable
        std::vector<std::size_t> actual_index_array;
        // the new buffer to be populated
        std::vector<double> new_buffer(array.get_buffer().size());
        // reverse the new shape vector
        std::reverse(new_shape.begin(), new_shape.end());
        // Now declare the new array
        NToyArray new_array(new_shape);
        // Recreate the buffer
        recursive_transpose_(
            shape,
            full_old_shape,
            new_shape,
            actual_index_array,
            array.get_buffer(),
            new_buffer,
            depth
        );
        // Overwrite the buffer
        new_array.set_buffer(new_buffer);
        return new_array;
    }
}
