#include <gtest/gtest.h>
#include "munkres-cpp/munkres.h"
#include "munkres-cpp/adapters/matrix_eigen.h"



class Adapters_eigen_matrix_Test : public ::testing::Test
{
};



TEST_F (Adapters_eigen_matrix_Test, solve_eigen_matrix_Success)
{
    // Arrange.
    static constexpr size_t dimension {3};
    munkres::matrix_eigen<double> etalon_eigen_matrix (dimension, dimension);
    //  {-1.0,  0.0, -1.0},
    //  { 0.0, -1.0, -1.0},
    //  {-1.0, -1.0,  0.0}
    etalon_eigen_matrix (0, 0) = -1.0; etalon_eigen_matrix (0, 1) =  0.0; etalon_eigen_matrix (0, 2) = -1.0;
    etalon_eigen_matrix (1, 0) =  0.0; etalon_eigen_matrix (1, 1) = -1.0; etalon_eigen_matrix (1, 2) = -1.0;
    etalon_eigen_matrix (2, 0) = -1.0; etalon_eigen_matrix (2, 1) = -1.0; etalon_eigen_matrix (2, 2) =  0.0;

    munkres::matrix_eigen<double> test_eigen_matrix (dimension, dimension);
    //  {1.0,  0.0,  1.0},
    //  {0.0,  1.0,  1.0},
    //  {1.0,  1.0,  0.0}
    test_eigen_matrix (0, 0) = 1.0; test_eigen_matrix (0, 1) = 0.0; test_eigen_matrix (0, 2) = 1.0;
    test_eigen_matrix (1, 0) = 0.0; test_eigen_matrix (1, 1) = 1.0; test_eigen_matrix (1, 2) = 1.0;
    test_eigen_matrix (2, 0) = 1.0; test_eigen_matrix (2, 1) = 1.0; test_eigen_matrix (2, 2) = 0.0;

    // Act.
    Munkres<double> solver;
    solver.solve (test_eigen_matrix);

    // Assert.
    for (unsigned int row = 0; row < dimension; ++row) {
        for (unsigned int col = 0; col < dimension; ++col) {
            EXPECT_EQ ( etalon_eigen_matrix (row, col), test_eigen_matrix (row, col) );
        }
    }
}

