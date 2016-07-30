#include <gtest/gtest.h>
#include "adapters/std_2d_vector.h"



class Adapters_std_2d_vector_Test : public ::testing::Test
{
};



TEST_F (Adapters_std_2d_vector_Test, resize_std_2d_vector_reduce_Success)
{
    // Arrange.
    std::vector<std::vector<double>> etalon_vector
    {
        {1.0},
        {4.0},
    };

    std::vector<std::vector<double>> test_vector
    {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };
    munkres::matrix_std_2d_vector<double> test_matrix (test_vector);

    // Act.
    test_matrix.resize (2, 1);

    // Assert.
    ASSERT_EQ (etalon_vector.size (), test_vector.size () );
    for (unsigned int row = 0; row < etalon_vector.size (); ++row) {
        ASSERT_EQ (etalon_vector [row].size (), test_vector [row].size () );
        for (unsigned int col = 0; col < etalon_vector [row].size (); ++col) {
            EXPECT_EQ (etalon_vector [row][col], test_vector [row][col]);
        }
    }
}



TEST_F (Adapters_std_2d_vector_Test, resize_std_2d_vector_increase_Success)
{
    // Arrange.
    std::vector<std::vector<double>> etalon_vector
    {
        {1.0, 2.0, 0.0},
        {3.0, 4.0, 0.0},
        {0.0, 0.0, 0.0}
    };

    std::vector<std::vector<double>> test_vector
    {
        {1.0,  2.0},
        {3.0,  4.0},
    };
    munkres::matrix_std_2d_vector<double> test_matrix (test_vector);

    // Act.
    test_matrix.resize (3, 3);

    // Assert.
    ASSERT_EQ (etalon_vector.size (), test_vector.size () );
    for (unsigned int row = 0; row < etalon_vector.size (); ++row) {
        ASSERT_EQ (etalon_vector [row].size (), test_vector [row].size () );
        for (unsigned int col = 0; col < etalon_vector [row].size (); ++col) {
            EXPECT_EQ (etalon_vector [row][col], test_vector [row][col]);
        }
    }
}



TEST_F (Adapters_std_2d_vector_Test, solve_std_2d_vector_Success)
{
    // Arrange.
    std::vector<std::vector<double>> etalon_vector
    {
        {-1.0,  0.0, -1.0},
        { 0.0, -1.0, -1.0},
        {-1.0, -1.0,  0.0}
    };
    std::vector<std::vector<double>> test_vector
    {
        {1.0,  0.0,  1.0},
        {0.0,  1.0,  1.0},
        {1.0,  1.0,  0.0}
    };
    munkres::matrix_std_2d_vector<double> test_matrix (test_vector);

    // Act.
    Munkres<double> solver;
    solver.solve (test_matrix);

    // Assert.
    ASSERT_EQ (etalon_vector.size (), test_vector.size () );
    for (unsigned int row = 0; row < etalon_vector.size (); ++row) {
        ASSERT_EQ (etalon_vector [row].size (), test_vector [row].size () );
        for (unsigned int col = 0; col < etalon_vector [row].size (); ++col) {
            EXPECT_EQ (etalon_vector [row][col], test_vector [row][col]);
        }
    }
}

