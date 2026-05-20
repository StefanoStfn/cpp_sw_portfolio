// SumOperator1D: Tests 1D elementwise addition and scalar addition broadcasting.
// SumOperator2D: Tests 2D elementwise addition and scalar addition broadcasting.
// SumOperatorMultiDim: Tests multidimensional addition, chained scalar operations, and shape mismatch validation.

#include <gtest/gtest.h>
#include "../include/numtoy_lib.h"

TEST(NToyArrayTest, SumOperator1D)
{
    // 1D Scalar
    numtoy::NToyArray a_array({1});
    numtoy::NToyArray b_array({1});
    a_array({0}) = 10.0;
    b_array({0}) = 12.0;
    numtoy::NToyArray c_array = a_array + b_array;
    EXPECT_DOUBLE_EQ(22.0, c_array({0}));
    // right side
    c_array = c_array+2.0;
    EXPECT_DOUBLE_EQ(24.0, c_array({0}));
    //left side
    c_array = 450.22222222 + c_array;
    EXPECT_DOUBLE_EQ(474.22222222, c_array({0}));
}


TEST(NToyArrayTest, SumOperator2D)
{
    // 2D
    const numtoy::NToyArray a_array({3,3});
    const numtoy::NToyArray b_array({3,3});
    numtoy::NToyArray c_array = a_array + b_array;
    EXPECT_DOUBLE_EQ(0.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(16.0, c_array({2,2}));
    // right side
    c_array = c_array+2;
    EXPECT_DOUBLE_EQ(2.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(10.0, c_array({1,1}));
    //left side
    c_array = 10.456 + c_array;
    EXPECT_DOUBLE_EQ(12.456, c_array({0,0}));
    EXPECT_DOUBLE_EQ(20.456, c_array({1,1}));
}

TEST(NToyArrayTest, SumOperatorMultiDim)
{
    //3D
    const numtoy::NToyArray d_array({3,3,3});
    const numtoy::NToyArray e_array({3,3,3});
    numtoy::NToyArray f_array = d_array + e_array;
    EXPECT_DOUBLE_EQ(0.0, f_array({0,0,0}));
    EXPECT_DOUBLE_EQ(52.0, f_array({2,2,2}));
    // right side
    f_array = f_array + 20.0;
    EXPECT_DOUBLE_EQ(72.0, f_array({2,2,2}));
    EXPECT_DOUBLE_EQ(22.0, f_array({0,0,1}));
    //left side
    f_array = 7.0 + f_array;
    EXPECT_DOUBLE_EQ(79.0, f_array({2,2,2}));
    EXPECT_DOUBLE_EQ(29.0, f_array({0,0,1}));
    // Shape Mismatch
    numtoy::NToyArray x_array({3,10,3});
    numtoy::NToyArray y_array({3,3,3});
    EXPECT_THROW(
        x_array+y_array,
        std::invalid_argument
    );
    x_array = numtoy::NToyArray({2,10,3,100,30});
    y_array = numtoy::NToyArray({2,3,3});
    EXPECT_THROW(
        x_array+y_array,
        std::invalid_argument
    );
}