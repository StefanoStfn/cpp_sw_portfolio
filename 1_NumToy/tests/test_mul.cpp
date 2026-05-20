// MulOperator1D: Tests 1D elementwise multiplication and scalar multiplication broadcasting.
// MulOperator2D: Tests 2D elementwise multiplication and scalar multiplication broadcasting.
// MulOperatorMultiDim: Tests multidimensional multiplication, chained scalar operations, and shape mismatch validation.

#include <gtest/gtest.h>
#include "../include/numtoy_lib.h"

TEST(NToyArrayTest, MulOperator1D)
{
    // 1D Scalar
    numtoy::NToyArray a_array({1});
    numtoy::NToyArray b_array({1});
    a_array({0}) = 10.0;
    b_array({0}) = 12.0;
    numtoy::NToyArray c_array = a_array * b_array;
    EXPECT_DOUBLE_EQ(120.0, c_array({0}));
    // right side
    c_array = c_array*2.0;
    EXPECT_DOUBLE_EQ(240.0, c_array({0}));
    //left side
    c_array = 0.0 * c_array;
    EXPECT_DOUBLE_EQ(0, c_array({0}));
}


TEST(NToyArrayTest, MulOperator2D)
{
    // 2D
    const numtoy::NToyArray a_array({3,3});
    const numtoy::NToyArray b_array({3,3});
    numtoy::NToyArray c_array = a_array * b_array;
    EXPECT_DOUBLE_EQ(0.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(64.0, c_array({2,2}));
    // right side
    c_array = c_array * 2;
    EXPECT_DOUBLE_EQ(0.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(32.0, c_array({1,1}));
    //left side
    c_array = 10.0 * c_array;
    EXPECT_DOUBLE_EQ(0.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(320.0, c_array({1,1}));
}

TEST(NToyArrayTest, MulOperatorMultiDim)
{
    //3D
    const numtoy::NToyArray d_array({2,2,2});
    const numtoy::NToyArray e_array({2,2,2});
    numtoy::NToyArray f_array = d_array * e_array;
    EXPECT_DOUBLE_EQ(0.0, f_array({0,0,0}));
    EXPECT_DOUBLE_EQ(49, f_array({1,1,1}));
    // right side
    f_array = f_array * 10.0;
    EXPECT_DOUBLE_EQ(490.0, f_array({1,1,1}));
    EXPECT_DOUBLE_EQ(10.0, f_array({0,0,1}));
    //left side
    f_array = 0.01 * f_array;
    EXPECT_DOUBLE_EQ(4.90, f_array({1,1,1}));
    EXPECT_DOUBLE_EQ(0.1, f_array({0,0,1}));
    // Shape Mismatch
    numtoy::NToyArray x_array({3,10,3});
    numtoy::NToyArray y_array({3,3,3});
    EXPECT_THROW(
        x_array*y_array,
        std::invalid_argument
    );
    x_array = numtoy::NToyArray({2,10,3,100,30});
    y_array = numtoy::NToyArray({2,3,3});
    EXPECT_THROW(
        x_array*y_array,
        std::invalid_argument
    );
}