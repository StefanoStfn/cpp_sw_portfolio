//
// Created by Martina on 20/05/2026.
//
#include <gtest/gtest.h>
#include "../include/numtoy_lib.h"

TEST(NToyArrayTest, ZerosArrayTest)
{
    numtoy::NToyArray zero_array = numtoy::zeros({4,4,4,4});
    std::size_t total_elements = 4*4*4*4;
    std::vector<double> array_buffer = zero_array.get_buffer();
    for (std::size_t i = 0; i < total_elements; ++i)
    {
        EXPECT_DOUBLE_EQ(array_buffer[i], 0.0);
    }
    zero_array = numtoy::zeros({3,3,3,2,2,2});
    total_elements = 3*3*3*2*2*2;
    array_buffer = zero_array.get_buffer();
    for (std::size_t i = 0; i < total_elements; ++i)
    {
        EXPECT_DOUBLE_EQ(array_buffer[i], 0.0);
    }
}

TEST(NToyArrayTest, OnesArrayTest)
{
    numtoy::NToyArray one_array = numtoy::ones({4,4,4,4});
    std::size_t total_elements = 4*4*4*4;
    std::vector<double> array_buffer = one_array.get_buffer();
    for (std::size_t i = 0; i < total_elements; ++i)
    {
        EXPECT_DOUBLE_EQ(array_buffer[i], 1.0);
    }
    one_array = numtoy::ones({3,3,3,2,2,2});
    total_elements = 3*3*3*2*2*2;
    array_buffer = one_array.get_buffer();
    for (std::size_t i = 0; i < total_elements; ++i)
    {
        EXPECT_DOUBLE_EQ(array_buffer[i], 1.0);
    }
}

TEST(NToyArrayTest, RandArrayTest)
{
    numtoy::NToyArray rand_array = numtoy::rand(
        {4,4,4,4},
        -2.0, //min
        2.0 //max
    );
    std::size_t total_elements = 4*4*4*4;
    std::vector<double> array_buffer = rand_array.get_buffer();
    for (std::size_t i = 0; i < total_elements; ++i)
    {
        EXPECT_TRUE(array_buffer[i] < 2.0);
        EXPECT_TRUE(array_buffer[i] >= -2.0);
    }
    rand_array = numtoy::rand(
        {3,3,3,2,2,2},
        -10.0, //min
        100.0 //max
    );
    total_elements = 3*3*3*2*2*2;
    array_buffer = rand_array.get_buffer();
    for (std::size_t i = 0; i < total_elements; ++i)
    {
        EXPECT_TRUE(array_buffer[i] < 100.0);
        EXPECT_TRUE(array_buffer[i] >= -10.0);
    }
}

TEST(NToyArrayTest, LongAlgebraTest)
{
    numtoy::NToyArray one_array = numtoy::ones({4,4,4,4});
    std::size_t total_elements = 4*4*4*4;
    // 2 * (10.5*1.0 - 9.0*1.0) = 3.0
    numtoy::NToyArray new_array = 2 * (10.50 * one_array - 9.0 / one_array);
    std::vector<double> array_buffer = new_array.get_buffer();
    for (std::size_t i = 0; i < total_elements; ++i)
    {
        EXPECT_TRUE(array_buffer[i] == 3.0);
    }
}

TEST(NToyArrayTest, TransposeArrayTest)
{
    //1D
    numtoy::NToyArray one_d_array({10});
    numtoy::NToyArray new_array = numtoy::transpose(one_d_array);
    std::vector<std::size_t> shape_vect = {10};
    EXPECT_TRUE(new_array.shape() == shape_vect);
    for (std::size_t i = 0; i < shape_vect[0]; ++i)
    {
        EXPECT_TRUE(new_array({i}) == (double)i);
    }

    // 2D
    numtoy::NToyArray two_d_array({3,4});
    new_array = numtoy::transpose(two_d_array);
    /*
     * 0 1 2 3
     * 4 5 6 7
     * 8 9 10 11
     *
     * Becomes
     *
     * 0 4 8
     * 1 5 9
     * 2 6 10
     * 3 7 11
     */
    EXPECT_DOUBLE_EQ(10.0 , new_array({2,2}));
    EXPECT_DOUBLE_EQ(1.0 , new_array({1,0}));
    EXPECT_DOUBLE_EQ(9.0 , new_array({1,2}));
    EXPECT_DOUBLE_EQ(0.0 , new_array({0,0}));
    EXPECT_DOUBLE_EQ(11.0 , new_array({3,2}));
    // 3D
    numtoy::NToyArray three_d_array({2,3,6});
    shape_vect = {6,3,2};
    new_array = numtoy::transpose(three_d_array);
    EXPECT_TRUE(new_array.shape() == shape_vect);
    EXPECT_TRUE(new_array({0,0,0}) == three_d_array({0,0,0}));
    EXPECT_TRUE(new_array({1,0,0}) == three_d_array({0,0,1}));
    EXPECT_TRUE(new_array({0,1,0}) == three_d_array({0,1,0}));
    EXPECT_TRUE(new_array({0,2,0}) == three_d_array({0,2,0}));
    EXPECT_TRUE(new_array({0,2,1}) == three_d_array({1,2,0}));
    EXPECT_TRUE(new_array({1,2,1}) == three_d_array({1,2,1}));
    EXPECT_TRUE(new_array({5,2,1}) == three_d_array({1,2,5}));

    // 4D
    numtoy::NToyArray four_d_array({1,2,3,4});
    new_array = numtoy::transpose(four_d_array);
    shape_vect = {4,3,2,1};
    EXPECT_TRUE(new_array.shape() == shape_vect);
    // indexing
    EXPECT_TRUE(new_array({0,0,0,0}) == four_d_array({0,0,0,0}));
    EXPECT_TRUE(new_array({1,0,0,0}) == four_d_array({0,0,0,1}));
    EXPECT_TRUE(new_array({0,1,0,0}) == four_d_array({0,0,1,0}));
    EXPECT_TRUE(new_array({0,2,0,0}) == four_d_array({0,0,2,0}));
    EXPECT_TRUE(new_array({0,2,1,0}) == four_d_array({0,1,2,0}));
    EXPECT_TRUE(new_array({1,2,1,0}) == four_d_array({0,1,2,1}));
    //5D
    numtoy::NToyArray five_d_array = numtoy::zeros({1,2,3,4,10});
    new_array = numtoy::transpose(five_d_array);
    shape_vect = {10,4,3,2,1};
    EXPECT_TRUE(new_array.shape() == shape_vect);
}
