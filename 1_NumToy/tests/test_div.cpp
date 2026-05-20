// DivOperator1D: Tests 1D elementwise division and scalar division broadcasting.
// DivOperator2D: Tests 2D division behavior including NaN propagation and scalar division broadcasting.
// DivOperatorMultiDim: Tests multidimensional division, chained scalar operations, and shape mismatch validation.

#include <cmath>
#include <gtest/gtest.h>
#include "../include/numtoy_lib.h"

TEST(NToyArrayTest, DivOperator1D)
{
    // 1D Scalar
    numtoy::NToyArray a_array({1});
    numtoy::NToyArray b_array({1});
    a_array({0}) = 12.0;
    b_array({0}) = 10.0;
    numtoy::NToyArray c_array = a_array / b_array;
    EXPECT_DOUBLE_EQ(1.2, c_array({0}));
    // right side
    c_array = c_array / 2.0;
    EXPECT_DOUBLE_EQ(0.6, c_array({0}));
    //left side
    c_array = 60.0 / c_array;
    EXPECT_DOUBLE_EQ(100.0, c_array({0}));
}


TEST(NToyArrayTest, DivOperator2D)
{
    // 2D
    const numtoy::NToyArray a_array({3,3});
    const numtoy::NToyArray b_array({3,3});
    numtoy::NToyArray c_array = a_array / b_array;
    EXPECT_TRUE(std::isnan(c_array({0,0})));
    EXPECT_DOUBLE_EQ(1.0, c_array({2,2}));
    // right side
    c_array = c_array / 2;
    EXPECT_TRUE(std::isnan(c_array({0,0})));
    EXPECT_DOUBLE_EQ(0.5, c_array({1,1}));
    //left side
    c_array = 50.0 / c_array;
    EXPECT_TRUE(std::isnan(c_array({0,0})));
    EXPECT_DOUBLE_EQ(100.0, c_array({1,1}));
}

TEST(NToyArrayTest, DivOperatorMultiDim)
{
    //3D
    const numtoy::NToyArray d_array({2,2,2});
    const numtoy::NToyArray e_array({2,2,2});
    numtoy::NToyArray f_array = d_array / e_array;
    EXPECT_TRUE(std::isnan(f_array({0,0,0})));
    EXPECT_DOUBLE_EQ(1, f_array({1,1,1}));
    // right side
    f_array = f_array / 10.0;
    EXPECT_DOUBLE_EQ(0.1, f_array({1,1,1}));
    EXPECT_DOUBLE_EQ(0.1, f_array({0,0,1}));
    //left side
    f_array = 0.01 / f_array;
    EXPECT_DOUBLE_EQ(0.1, f_array({1,1,1}));
    EXPECT_DOUBLE_EQ(0.1, f_array({0,0,1}));
    // Shape Mismatch
    numtoy::NToyArray x_array({3,10,3});
    numtoy::NToyArray y_array({3,3,3});
    EXPECT_THROW(
        x_array / y_array,
        std::invalid_argument
    );
    x_array = numtoy::NToyArray({2,10,3,100,30});
    y_array = numtoy::NToyArray({2,3,3});
    EXPECT_THROW(
        x_array / y_array,
        std::invalid_argument
    );
}