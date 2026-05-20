// Reading: Tests multidimensional indexing, shape validation, and out-of-bounds exception handling.
// Writing: Tests multidimensional element assignment and mutation persistence.

#include <gtest/gtest.h>
#include "../include/numtoy_lib.h"

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
    numtoy::NToyArray b_array({3,3,31,1});
    EXPECT_DOUBLE_EQ(30.0, b_array({0,0,30,0}));
    b_array({2,2,0,0}) = 3.402;
    EXPECT_DOUBLE_EQ(3.402, b_array({2,2,0,0}));
    b_array({1,2,30,0}) = 0.00102;
    EXPECT_DOUBLE_EQ(0.00102, b_array({1,2,30,0}));
}


