//
// Created by Martina on 18/05/2026.
//

#include <gtest/gtest.h>
#include "../include/numtoy_lib.h"

TEST(NtoyArrayTest, AllScalarTests)
{
    // Scalar Array and Scalar
    numtoy::NToyArray a_array({1});
    EXPECT_DOUBLE_EQ(0.0, a_array({0}));
    a_array = a_array + 20.0;
    EXPECT_DOUBLE_EQ(20.0, a_array({0}));
    a_array = a_array - 5.0;
    EXPECT_DOUBLE_EQ(15.0, a_array({0}));
    a_array = a_array * 2.0;
    EXPECT_DOUBLE_EQ(30.0, a_array({0}));
    a_array = a_array / 3.0;
    EXPECT_DOUBLE_EQ(10.0, a_array({0}));
    // Shape Mismatch checks
    EXPECT_THROW(a_array({0,3}),std::invalid_argument);
    EXPECT_THROW(a_array({1}),std::invalid_argument);
    // Scalar Array and Scalar Array
    numtoy::NToyArray b_array({1});
    numtoy::NToyArray c_array = a_array + b_array;
    EXPECT_DOUBLE_EQ(10.0, c_array({0}));
    a_array({0}) = 80.0;
    b_array({0}) = 40.0;
    c_array = a_array - b_array;
    EXPECT_DOUBLE_EQ(40.0, c_array({0}));
    a_array({0}) = 3.5;
    b_array({0}) = 4.0;
    c_array = a_array * b_array;
    EXPECT_DOUBLE_EQ(14.0, c_array({0}));
    a_array({0}) = 10;
    b_array({0}) = 4.0;
    c_array = a_array / b_array;
    EXPECT_DOUBLE_EQ(2.5, c_array({0}));
}

TEST(NToyArrayTest, Reading)
{
    // 2D
    numtoy::NToyArray a_array({3,3});
    EXPECT_DOUBLE_EQ(8.0, a_array({2,2}));
    EXPECT_DOUBLE_EQ(0.0, a_array({0,0}));
    EXPECT_DOUBLE_EQ(1.0, a_array({0,1}));
    // 3D
    numtoy::NToyArray b_array({5,5,5});
    EXPECT_DOUBLE_EQ(60.0, b_array({2,2,0}));
    EXPECT_DOUBLE_EQ(0.0, b_array({0,0,0}));
    EXPECT_DOUBLE_EQ(5.0, b_array({0,1,0}));
    // Throw exception --> a_array
    EXPECT_THROW(a_array({3,3}),std::invalid_argument);
    EXPECT_THROW(a_array({0,7,32}),std::invalid_argument);
    // Throw exception --> b_array
    EXPECT_THROW(b_array({3,3}),std::invalid_argument);
    EXPECT_THROW(b_array({0,7,32}),std::invalid_argument);
    EXPECT_THROW(b_array({0,7,0}),std::invalid_argument);
    EXPECT_THROW(b_array({0,2,0,1}),std::invalid_argument);
    // Shape Checks
    EXPECT_EQ(
        std::vector<std::size_t>({3,3}),
        a_array.shape()
    );
    EXPECT_EQ(
        std::vector<std::size_t>({5,5,5}),
        b_array.shape()
    );
}

TEST(NToyArrayTest, Writing)
{
    numtoy::NToyArray a_array({3,3});
    EXPECT_DOUBLE_EQ(8.0, a_array({2,2}));
    a_array({2,2}) = 3.402;
    EXPECT_DOUBLE_EQ(3.402, a_array({2,2}));
    a_array({0,0}) = 0.00102;
    EXPECT_DOUBLE_EQ(0.00102, a_array({0,0}));
    EXPECT_DOUBLE_EQ(3.402, a_array({2,2}));
}

TEST(NToyArrayTest, SumOperator)
{
    // 2D
    const numtoy::NToyArray a_array({3,3});
    const numtoy::NToyArray b_array({3,3});
    numtoy::NToyArray c_array = a_array + b_array;
    EXPECT_DOUBLE_EQ(0.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(16.0, c_array({2,2}));
    c_array = c_array+2;
    EXPECT_DOUBLE_EQ(2.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(10.0, c_array({1,1}));
    //3D
    const numtoy::NToyArray d_array({3,3,3});
    const numtoy::NToyArray e_array({3,3,3});
    numtoy::NToyArray f_array = d_array + e_array;
    EXPECT_DOUBLE_EQ(0.0, f_array({0,0,0}));
    EXPECT_DOUBLE_EQ(52.0, f_array({2,2,2}));
    f_array = f_array + 20.0;
    EXPECT_DOUBLE_EQ(72.0, f_array({2,2,2}));
    EXPECT_DOUBLE_EQ(22.0, f_array({0,0,1}));
    // Shape Missmatch
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

TEST (NtoyArrayTest, DifferenceOperator)
{
    // 2D
    const numtoy::NToyArray a_array({3,3});
    const numtoy::NToyArray b_array({3,3});
    numtoy::NToyArray c_array = a_array - b_array;
    EXPECT_DOUBLE_EQ(0.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(0.0, c_array({1,2}));
    EXPECT_DOUBLE_EQ(0.0, c_array({0,2}));
    EXPECT_DOUBLE_EQ(0.0, c_array({2,2}));
    c_array = c_array+2;
    EXPECT_DOUBLE_EQ(2.0, c_array({0,0}));
    EXPECT_DOUBLE_EQ(2.0, c_array({1,1}));
    // 4D
    const numtoy::NToyArray d_array({3,3,4,5});
    const numtoy::NToyArray e_array({3,3,4,5});
    numtoy::NToyArray f_array = d_array - e_array;
    EXPECT_DOUBLE_EQ(0.0, f_array({0,0,2,4}));
    EXPECT_DOUBLE_EQ(0.0, f_array({1,2,1,2}));
    EXPECT_DOUBLE_EQ(0.0, f_array({0,2,2,3}));
    EXPECT_DOUBLE_EQ(0.0, f_array({2,2,1,4}));
    f_array = f_array + 210.0;
    EXPECT_DOUBLE_EQ(210.0, f_array({0,0,1,3}));
    EXPECT_DOUBLE_EQ(210.0, f_array({1,1,1,3}));
    EXPECT_DOUBLE_EQ(210.0, f_array({2,2,3,3}));
    EXPECT_DOUBLE_EQ(210.0, f_array({1,1,2,4}));
}
