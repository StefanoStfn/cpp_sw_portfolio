
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
            std::string to_string();
            // Access Operator
            double& operator() (const std::vector<std::size_t>& indices);
            // Sum operators
            NToyArray operator+ (const NToyArray& b_array) const;
            NToyArray operator+ (double b) const;
            // Difference Operators
            NToyArray operator- (const NToyArray& b_array) const;
            NToyArray operator- (double b) const;
            NToyArray operator-() const;
            // Multiplication
            NToyArray operator* (const NToyArray& b_array) const;
            NToyArray operator* (double b) const;
            // Division
            NToyArray operator/ (const NToyArray& b_array) const;
            NToyArray operator/ (double b) const;


        private:
            // Variables
            std::vector<std::size_t> shape_;
            std::vector<double> buffer_;
            // Methods
            std::size_t compute_index_(const std::vector<std::size_t>& indices);
            void recursive_traversal_ (
                std::vector<std::size_t>& shape,
                std::vector<std::size_t>& actual_index_array,
                const std::vector<double>& buffer,
                std::size_t depth,
                std::ostringstream& oss
            );
    };
}


#endif //INC_1_NUMTOY_NTOYARRAY_H
