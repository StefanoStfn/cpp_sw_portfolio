//
// Created by Martina on 20/05/2026.
//
#include <gtest/gtest.h>
#include "../include/numtoy_lib.h"

TEST(NToyArrayTest, DiffOperator1D)
{
    // 1D Scalar
    numtoy::NToyArray a_array({1});
    numtoy::NToyArray b_array({1});
    a_array({0}) = 10.0;
    b_array({0}) = 12.0;
    numtoy::NToyArray c_array = a_array - b_array;
    EXPECT_DOUBLE_EQ(-2.0, c_array({0}));
    // right side
    c_array = c_array+2.0;
    EXPECT_DOUBLE_EQ(0.0, c_array({0}));
    //left side
    c_array = 450.22222222 - c_array;
    EXPECT_DOUBLE_EQ(450.22222222, c_array({0}));
}


TEST(NToyArrayTest, DiffOperator2D)
{
    // 2D
    const numtoy::NToyArray a_array({3,3});
    const numtoy::NToyArray b_array({3,3});
    numtoy::NToyArray c_array = a_array - b_array;
    EXPECT_DOUBLE_EQ(0.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(0.0, c_array({2,2}));
    // right side
    c_array = c_array-2;
    EXPECT_DOUBLE_EQ(-2.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(-2.0, c_array({1,1}));
    //left side
    c_array = 10.456 - c_array;
    EXPECT_DOUBLE_EQ(12.456, c_array({0,0}));
    EXPECT_DOUBLE_EQ(12.456, c_array({1,1}));
}

TEST(NToyArrayTest, DiffOperatorMultiDim)
{
    //3D
    const numtoy::NToyArray d_array({3,3,3});
    const numtoy::NToyArray e_array({3,3,3});
    numtoy::NToyArray f_array = d_array - 2 * e_array;
    EXPECT_DOUBLE_EQ(0.0, f_array({0,0,0}));
    EXPECT_DOUBLE_EQ(-26.0, f_array({2,2,2}));
    // right side
    f_array = f_array - 20.0;
    EXPECT_DOUBLE_EQ(-46.0, f_array({2,2,2}));
    EXPECT_DOUBLE_EQ(-21.0, f_array({0,0,1}));
    //left side
    f_array = 7.0 - f_array;
    EXPECT_DOUBLE_EQ(53.0, f_array({2,2,2}));
    EXPECT_DOUBLE_EQ(28.0, f_array({0,0,1}));
    // Shape tch
    numtoy::NToyArray x_array({3,10,3});
    numtoy::NToyArray y_array({3,3,3});
    EXPECT_THROW(
        x_array-y_array,
        std::invalid_argument
    );
    x_array = numtoy::NToyArray({2,10,3,100,30});
    y_array = numtoy::NToyArray({2,3,3});
    EXPECT_THROW(
        x_array-y_array,
        std::invalid_argument
    );
}