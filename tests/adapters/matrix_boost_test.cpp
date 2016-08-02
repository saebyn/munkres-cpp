#include <gtest/gtest.h>
#include "munkres-cpp/munkres.h"
#include "munkres-cpp/adapters/matrix_boost.h"



class Adapters_boost_matrix_Test : public ::testing::Test
{
};



TEST_F (Adapters_boost_matrix_Test, resize_boost_matrix_reduce_Success)
{
    // Arrange.
    munkres::matrix_boost<double> etalon_boost_matrix (2, 1);
    //  {1.0},
    //  {4.0},
    etalon_boost_matrix (0, 0) = 1.0;
    etalon_boost_matrix (1, 0) = 4.0;

    munkres::matrix_boost<double> test_boost_matrix (3, 3);
    //  {1.0, 2.0, 3.0},
    //  {4.0, 5.0, 6.0},
    //  {7.0, 8.0, 9.0}
    test_boost_matrix (0, 0) =  1.0; test_boost_matrix (0, 1) =  2.0; test_boost_matrix (0, 2) =  3.0;
    test_boost_matrix (1, 0) =  4.0; test_boost_matrix (1, 1) =  5.0; test_boost_matrix (1, 2) =  6.0;
    test_boost_matrix (2, 0) =  7.0; test_boost_matrix (2, 1) =  8.0; test_boost_matrix (2, 2) =  9.0;

    // Act.
    test_boost_matrix.resize (2, 1);

    // Assert.
    ASSERT_EQ (etalon_boost_matrix.rows (), test_boost_matrix.rows () );
    ASSERT_EQ (etalon_boost_matrix.columns (), test_boost_matrix.columns () );
    for (unsigned int row = 0; row < etalon_boost_matrix.rows (); ++row) {
        for (unsigned int col = 0; col < etalon_boost_matrix.columns (); ++col) {
            EXPECT_EQ ( etalon_boost_matrix (row, col), test_boost_matrix (row, col) );
        }
    }
}



TEST_F (Adapters_boost_matrix_Test, resize_boost_matrix_increase_Success)
{
    // Arrange.
    munkres::matrix_boost<double> etalon_boost_matrix (3, 3);
    //  {1.0, 2.0, 0.0},
    //  {3.0, 4.0, 0.0},
    //  {0.0, 0.0, 0.0}
    etalon_boost_matrix (0, 0) =  1.0; etalon_boost_matrix (0, 1) =  2.0; etalon_boost_matrix (0, 2) =  0.0;
    etalon_boost_matrix (1, 0) =  3.0; etalon_boost_matrix (1, 1) =  4.0; etalon_boost_matrix (1, 2) =  0.0;
    etalon_boost_matrix (2, 0) =  0.0; etalon_boost_matrix (2, 1) =  0.0; etalon_boost_matrix (2, 2) =  0.0;

    munkres::matrix_boost<double> test_boost_matrix (2, 2);
    //  {1.0, 2.0},
    //  {3.0, 4.0},
    test_boost_matrix (0, 0) =  1.0; test_boost_matrix (0, 1) =  2.0;
    test_boost_matrix (1, 0) =  3.0; test_boost_matrix (1, 1) =  4.0;

    // Act.
    test_boost_matrix.resize (3, 3);

    // Assert.
    ASSERT_EQ (etalon_boost_matrix.rows (), test_boost_matrix.rows () );
    ASSERT_EQ (etalon_boost_matrix.columns (), test_boost_matrix.columns () );
    for (unsigned int row = 0; row < etalon_boost_matrix.rows (); ++row) {
        for (unsigned int col = 0; col < etalon_boost_matrix.columns (); ++col) {
            EXPECT_EQ ( etalon_boost_matrix (row, col), test_boost_matrix (row, col) );
        }
    }
}



TEST_F (Adapters_boost_matrix_Test, solve_boost_matrix_Success)
{
    // Arrange.
    constexpr unsigned int dimension {3};
    munkres::matrix_boost<double> etalon_boost_matrix (dimension, dimension);
    //  {-1.0,  0.0, -1.0},
    //  { 0.0, -1.0, -1.0},
    //  {-1.0, -1.0,  0.0}
    etalon_boost_matrix (0, 0) = -1.0; etalon_boost_matrix (0, 1) =  0.0; etalon_boost_matrix (0, 2) = -1.0;
    etalon_boost_matrix (1, 0) =  0.0; etalon_boost_matrix (1, 1) = -1.0; etalon_boost_matrix (1, 2) = -1.0;
    etalon_boost_matrix (2, 0) = -1.0; etalon_boost_matrix (2, 1) = -1.0; etalon_boost_matrix (2, 2) =  0.0;

    munkres::matrix_boost<double> test_boost_matrix (dimension, dimension);
    //  {1.0,  0.0,  1.0},
    //  {0.0,  1.0,  1.0},
    //  {1.0,  1.0,  0.0}
    test_boost_matrix (0, 0) = 1.0; test_boost_matrix (0, 1) = 0.0; test_boost_matrix (0, 2) = 1.0;
    test_boost_matrix (1, 0) = 0.0; test_boost_matrix (1, 1) = 1.0; test_boost_matrix (1, 2) = 1.0;
    test_boost_matrix (2, 0) = 1.0; test_boost_matrix (2, 1) = 1.0; test_boost_matrix (2, 2) = 0.0;

    // Act.
    Munkres<double> solver;
    solver.solve (test_boost_matrix);

    // Assert.
    for (unsigned int row = 0; row < dimension; ++row) {
        for (unsigned int col = 0; col < dimension; ++col) {
            EXPECT_EQ ( etalon_boost_matrix (row, col), test_boost_matrix (row, col) );
        }
    }
}

