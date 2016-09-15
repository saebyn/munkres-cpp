#include <gtest/gtest.h>
#include "munkres-cpp/munkres.h"
#include "munkres-cpp/adapters/matrix_eigen.h"



class Adapters_eigen_matrix_Test : public ::testing::Test
{
};



TEST_F (Adapters_eigen_matrix_Test, resize_eigen_matrix_reduce_Success)
{
    // Arrange.
    munkres_cpp::matrix_eigen<double> etalon_eigen_matrix (2, 1);
    //  {1.0},
    //  {4.0},
    etalon_eigen_matrix (0, 0) = 1.0;
    etalon_eigen_matrix (1, 0) = 4.0;

    munkres_cpp::matrix_eigen<double> test_eigen_matrix (3, 3);
    //  {1.0, 2.0, 3.0},
    //  {4.0, 5.0, 6.0},
    //  {7.0, 8.0, 9.0}
    test_eigen_matrix (0, 0) = 1.0; test_eigen_matrix (0, 1) = 2.0; test_eigen_matrix (0, 2) = 3.0;
    test_eigen_matrix (1, 0) = 4.0; test_eigen_matrix (1, 1) = 5.0; test_eigen_matrix (1, 2) = 6.0;
    test_eigen_matrix (2, 0) = 7.0; test_eigen_matrix (2, 1) = 8.0; test_eigen_matrix (2, 2) = 9.0;

    // Act.
    test_eigen_matrix.resize (2, 1);

    // Assert.
    ASSERT_EQ (etalon_eigen_matrix.rows (), test_eigen_matrix.rows () );
    ASSERT_EQ (etalon_eigen_matrix.columns (), test_eigen_matrix.columns () );
    for (unsigned int row = 0; row < etalon_eigen_matrix.rows (); ++row) {
        for (unsigned int col = 0; col < etalon_eigen_matrix.columns (); ++col) {
            EXPECT_EQ ( etalon_eigen_matrix (row, col), test_eigen_matrix (row, col) );
        }
    }
}



TEST_F (Adapters_eigen_matrix_Test, resize_eigen_matrix_increase_Success)
{
    // Arrange.
    munkres_cpp::matrix_eigen<double> etalon_eigen_matrix (3, 3);
    //  {1.0, 2.0, 0.0},
    //  {3.0, 4.0, 0.0},
    //  {0.0, 0.0, 0.0}
    etalon_eigen_matrix (0, 0) = 1.0; etalon_eigen_matrix (0, 1) = 2.0; etalon_eigen_matrix (0, 2) = 0.0;
    etalon_eigen_matrix (1, 0) = 3.0; etalon_eigen_matrix (1, 1) = 4.0; etalon_eigen_matrix (1, 2) = 0.0;
    etalon_eigen_matrix (2, 0) = 0.0; etalon_eigen_matrix (2, 1) = 0.0; etalon_eigen_matrix (2, 2) = 0.0;

    munkres_cpp::matrix_eigen<double> test_eigen_matrix (2, 2);
    //  {1.0, 2.0},
    //  {3.0, 4.0},
    test_eigen_matrix (0, 0) = 1.0; test_eigen_matrix (0, 1) = 2.0;
    test_eigen_matrix (1, 0) = 3.0; test_eigen_matrix (1, 1) = 4.0;

    // Act.
    test_eigen_matrix.resize (3, 3);

    // Assert.
    ASSERT_EQ (etalon_eigen_matrix.rows (), test_eigen_matrix.rows () );
    ASSERT_EQ (etalon_eigen_matrix.columns (), test_eigen_matrix.columns () );
    for (unsigned int row = 0; row < etalon_eigen_matrix.rows (); ++row) {
        for (unsigned int col = 0; col < etalon_eigen_matrix.columns (); ++col) {
            EXPECT_EQ ( etalon_eigen_matrix (row, col), test_eigen_matrix (row, col) );
        }
    }
}



TEST_F (Adapters_eigen_matrix_Test, solve_eigen_matrix_Success)
{
    // Arrange.
    static constexpr size_t dimension {3};
    munkres_cpp::matrix_eigen<double> etalon_eigen_matrix (dimension, dimension);
    //  {1.0,  0.0,  1.0},
    //  {0.0,  1.0,  1.0},
    //  {1.0,  1.0,  0.0}
    etalon_eigen_matrix (0, 0) = 1.0; etalon_eigen_matrix (0, 1) = 0.0; etalon_eigen_matrix (0, 2) = 1.0;
    etalon_eigen_matrix (1, 0) = 0.0; etalon_eigen_matrix (1, 1) = 1.0; etalon_eigen_matrix (1, 2) = 1.0;
    etalon_eigen_matrix (2, 0) = 1.0; etalon_eigen_matrix (2, 1) = 1.0; etalon_eigen_matrix (2, 2) = 0.0;

    munkres_cpp::matrix_eigen<double> test_eigen_matrix (dimension, dimension);
    //  {9.0,  0.0,  9.0},
    //  {0.0,  9.0,  9.0},
    //  {9.0,  9.0,  0.0}
    test_eigen_matrix (0, 0) = 9.0; test_eigen_matrix (0, 1) = 0.0; test_eigen_matrix (0, 2) = 9.0;
    test_eigen_matrix (1, 0) = 0.0; test_eigen_matrix (1, 1) = 9.0; test_eigen_matrix (1, 2) = 9.0;
    test_eigen_matrix (2, 0) = 9.0; test_eigen_matrix (2, 1) = 9.0; test_eigen_matrix (2, 2) = 0.0;

    // Act.
    munkres_cpp::Munkres<double> solver;
    solver.solve (test_eigen_matrix);

    // Assert.
    for (unsigned int row = 0; row < dimension; ++row) {
        for (unsigned int col = 0; col < dimension; ++col) {
            EXPECT_EQ ( etalon_eigen_matrix (row, col), test_eigen_matrix (row, col) );
        }
    }
}

