/*
From Numpy Documentation: https://github.com/numpy/numpy/blob/main/doc/source/reference/arrays.ndarray.rst#id1

"An instance of class :class:`ndarray` consists of a contiguous one-dimensional segment of computer memory
(owned by the array, or by some other object), combined with an indexing scheme that
maps N integers into the location of an item in the block."

"A segment of memory is inherently 1-dimensional, and there are many different schemes
for arranging the items of an N-dimensional array in a 1-dimensional block."

Note of the author:
CPUs are obviously optimized to run instructions sequentially.
Doing Program Counter (PC) = PC + 1 in the microcode, or in the memory address is so cheap that it would be
naive if that operation wouldn't be super optimized by electronics engineers.

*/

#ifndef INC_1_NUMTOY_NTOYARRAY_H
#define INC_1_NUMTOY_NTOYARRAY_H

#include <vector>

namespace numtoy
{
    class NToyArray
    {
        public:
            NToyArray(std::vector<std::size_t> shape);
            std::vector<std::size_t> shape() const { return shape_; };
            double& operator() (const std::vector<std::size_t>& indices);
            // Sum operators
            numtoy::NToyArray operator+ (const numtoy::NToyArray& b_array) const;
            numtoy::NToyArray operator+ (double b) const;
            // Difference Operators
            numtoy::NToyArray operator- (const numtoy::NToyArray& b_array) const;
            numtoy::NToyArray operator- (double b) const;
            // Multiplication
            numtoy::NToyArray operator* (const numtoy::NToyArray& b_array) const;
            numtoy::NToyArray operator* (double b) const;
            // Division
            numtoy::NToyArray operator/ (const numtoy::NToyArray& b_array) const;
            numtoy::NToyArray operator/ (double b) const;

        private:
            // Variables
            std::vector<std::size_t> shape_;
            std::vector<double> buffer_;
            // Methods
            std::size_t compute_index_(const std::vector<std::size_t>& indices);
            void overwrite_buffer_(const std::vector<double>& buffer) { buffer_ = buffer; };
    };
}


#endif //INC_1_NUMTOY_NTOYARRAY_H
