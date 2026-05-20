
#include <numeric>
#include <sstream>
#include <algorithm>
#include "../include/ntoyarray.h"

namespace numtoy
{
    NToyArray::NToyArray(std::vector<std::size_t> shape)
    {
        for (std::size_t i = 0; i < shape.size(); ++i)
        {
            if (shape[i] == 0)
            {
                throw std::invalid_argument(
                    "Cannot create Multidimensional Array with zero shape dimensions"
                );
            }
        }
        this->shape_ = shape;
        const std::size_t buffer_shape = std::accumulate(
            shape.begin(),
            shape.end(),
            std::size_t{1},
            std::multiplies<std::size_t>());
        buffer_.resize(buffer_shape);
        // Dummy initialization
        for (std::size_t i = 0; i < buffer_shape; ++i)
        {
            buffer_[i] = (double)i;
        }
    }

    void NToyArray::set_buffer(const std::vector<double>& buffer)
    {
        if (buffer.size() != this->buffer_.size())
        {
            std::ostringstream oss;
            oss << "Buffer Size Mismatch, cannot overwrite it. ";
            oss << "Provided Length: " << buffer.size() << ". ";
            oss << "Expected " << this->buffer_.size() << std::endl;
            throw std::invalid_argument(
                oss.str()
            );
        }
        this->buffer_ = buffer;
    }

    double& NToyArray::operator()(const std::vector<std::size_t>& indices)
    {
        std::ostringstream oss;
        std::vector<int> dimension_check(indices.size(), 0);
        // Check if access is done using the correct number of indices
        if (indices.size() != shape_.size())
        {
            oss << "Indices-Shape dimension missmatch, ";
            oss << "Expected " << shape_.size() << " elements. ";
            oss << indices.size() << " were passed.";
            throw std::invalid_argument(oss.str());
        }
        // Check if there are indices outside shape axis dimensions
        for (std::size_t i = 0; i < indices.size(); ++i)
        {
            if (indices[i] >= shape_[i])
            {
                oss << "Specified Axis index in position " << i << " is " << indices[i] << ", ";
                oss << "Expected Max Index " << shape_[i]-1 << ".\n";
                dimension_check[i] = 1;
            }
        }
        if (std::accumulate(dimension_check.begin(), dimension_check.end(), 0) > 0)
        {
            throw std::invalid_argument(oss.str());
        }
        else
        {
            return buffer_[this->compute_index_(indices)];
        }
    }

    std::size_t NToyArray::compute_index_(const std::vector<std::size_t>& indices)
    {
        /*
         * Given an index vector, this multiplies the shape iteratively
         * and return an index for the buffer.
         * This same result can be obtained recursively too!
         */
        std::vector<std::size_t> stride_vector(shape_.size(), 1);
        std::vector<std::size_t> tmp_multiply(shape_.size());
        std::size_t out_index;
        for (size_t i = 0; i < shape_.size()-1; ++i)
        {
            stride_vector[i] = std::accumulate(
                shape_.begin()+i+std::size_t{1},
                shape_.end(),
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
        out_index = std::accumulate(
            tmp_multiply.begin(),
            tmp_multiply.end(),
            std::size_t{0}
        );
        return out_index;
    }

    // Sum operators
    numtoy::NToyArray NToyArray::operator+ (const numtoy::NToyArray& b_array) const
    {
        std::ostringstream oss;
        if (shape_ != b_array.shape())
        {
            oss << "MultiDim Array Dimension missmatch. Sum is not possible.";
            oss << " ( ";
            for (int i = 0; i < shape_.size(); ++i)
            {
                oss << shape_[i] << ", ";
            }

            oss << ") != ( ";
            for (int i = 0; i < shape_.size(); ++i)
            {
                oss << b_array.shape()[i] << ", ";
            }
            oss << ")";
            throw std::invalid_argument(
                oss.str()
            );
        }
        // Check is done, now let's create the new buffer
        numtoy::NToyArray new_array(shape_);
        std::transform(
            this->buffer_.begin(),
            this->buffer_.end(),
            b_array.buffer_.begin(),
            new_array.buffer_.begin(),
            [](double a, double b){return a+b;}
        );
        return new_array;
    }

    numtoy::NToyArray NToyArray::operator+ (double b) const
    {
        numtoy::NToyArray new_array(shape_);
        std::transform(
            buffer_.begin(),
            buffer_.end(),
            new_array.buffer_.begin(),
            [b](const double& a){return a+b;}
        );
        return new_array;
    }

    numtoy::NToyArray NToyArray::operator- (const numtoy::NToyArray& b_array) const
    {
        std::ostringstream oss;
        if (shape_ != b_array.shape())
        {
            oss << "MultiDim Array Dimension missmatch. Difference is not possible.";
            oss << " ( ";
            for (int i = 0; i < shape_.size(); ++i)
            {
                oss << shape_[i] << ", ";
            }

            oss << ") != ( ";
            for (int i = 0; i < shape_.size(); ++i)
            {
                oss << b_array.shape()[i] << ", ";
            }
            oss << ")";
            throw std::invalid_argument(
                oss.str()
            );
        }
        // Check is done, now let's create the new buffer
        numtoy::NToyArray new_array(shape_);
        std::transform(
            this->buffer_.begin(),
            this->buffer_.end(),
            b_array.buffer_.begin(),
            new_array.buffer_.begin(),
            [](double a, double b){return a-b;}
        );
        return new_array;
    }

    numtoy::NToyArray NToyArray::operator- (double b) const
    {
        numtoy::NToyArray new_array(shape_);
        std::transform(
            buffer_.begin(),
            buffer_.end(),
            new_array.buffer_.begin(),
            [b](double a){return a-b;}
        );
        return new_array;
    }

    // Multiplication
    numtoy::NToyArray NToyArray::operator* (const numtoy::NToyArray& b_array) const
    {
        std::ostringstream oss;
        if (shape_ != b_array.shape())
        {
            oss << "MultiDim Array Dimension missmatch. element-Wise Multiplication is not possible.";
            oss << " ( ";
            for (int i = 0; i < shape_.size(); ++i)
            {
                oss << shape_[i] << ", ";
            }

            oss << ") != ( ";
            for (int i = 0; i < shape_.size(); ++i)
            {
                oss << b_array.shape()[i] << ", ";
            }
            oss << ")";
            throw std::invalid_argument(
                oss.str()
            );
        }
        // Check is done, now let's create the new buffer
        numtoy::NToyArray new_array(shape_);
        std::transform(
            this->buffer_.begin(),
            this->buffer_.end(),
            b_array.buffer_.begin(),
            new_array.buffer_.begin(),
            [](double a, double b){return a*b;}
        );
        return new_array;
    }

    numtoy::NToyArray NToyArray::operator* (double b) const
    {
        numtoy::NToyArray new_array(shape_);
        std::transform(
            buffer_.begin(),
            buffer_.end(),
            new_array.buffer_.begin(),
            [b](double a){return a*b;}
        );
        return new_array;
    }

    // Division
    numtoy::NToyArray NToyArray::operator/ (const numtoy::NToyArray& b_array) const
    {
        std::ostringstream oss;
        if (shape_ != b_array.shape())
        {
            oss << "MultiDim Array Dimension missmatch. Element-Wise Division is not possible.";
            oss << " ( ";
            for (int i = 0; i < shape_.size(); ++i)
            {
                oss << shape_[i] << ", ";
            }

            oss << ") != ( ";
            for (int i = 0; i < shape_.size(); ++i)
            {
                oss << b_array.shape()[i] << ", ";
            }
            oss << ")";
            throw std::invalid_argument(
                oss.str()
            );
        }
        // Check is done, now let's create the new buffer
        numtoy::NToyArray new_array(shape_);
        std::transform(
            this->buffer_.begin(),
            this->buffer_.end(),
            b_array.buffer_.begin(),
            new_array.buffer_.begin(),
            [](double a, double b){return a/b;}
        );
        return new_array;
    }

    numtoy::NToyArray NToyArray::operator/ (double b) const
    {
        numtoy::NToyArray new_array(shape_);
        std::transform(
            buffer_.begin(),
            buffer_.end(),
            new_array.buffer_.begin(),
            [b](double a){return a/b;}
        );
        return new_array;
    }
}
