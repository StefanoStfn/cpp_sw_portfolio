
// NToyArray Constructor: Validates multidimensional shape construction and contiguous buffer initialization.
// NToyArray::set_buffer: Validates safe buffer replacement while preserving shape-buffer invariants.
// NToyArray::operator(): Tests multidimensional element access, shape validation, and bounds checking.
// NToyArray::compute_index_: Maps multidimensional indices into contiguous row-major buffer offsets.
// NToyArray::operator+: Implements elementwise multidimensional addition and scalar broadcasting.
// NToyArray::operator-: Implements elementwise multidimensional subtraction and scalar broadcasting.
// NToyArray::operator*: Implements elementwise multidimensional multiplication and scalar broadcasting.
// NToyArray::operator/: Implements elementwise multidimensional division and scalar broadcasting.
// --> left side operand is implemented in the numtoy_lib files

#ifndef INC_1_NUMTOY_NTOYARRAY_H
#define INC_1_NUMTOY_NTOYARRAY_H

#include <vector>

namespace numtoy
{
    class NToyArray
    {
        public:
            NToyArray(std::vector<std::size_t> shape);
            NToyArray(std::vector<std::size_t> shape, std::vector<double> data);
            const std::vector<std::size_t>& shape() const { return shape_; };
            std::string shape_string() const;
            // Buffer Access
            const std::vector<double>& get_buffer() const { return buffer_; };
            void set_buffer(const std::vector<double>& buffer);
            // Access Operator
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
    };
}


#endif //INC_1_NUMTOY_NTOYARRAY_H
