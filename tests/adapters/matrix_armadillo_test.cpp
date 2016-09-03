#include <gtest/gtest.h>
#include "munkres-cpp/munkres.h"
#include "munkres-cpp/adapters/matrix_armadillo.h"



class Adapters_armadillo_matrix_Test : public ::testing::Test
{
};



TEST_F (Adapters_armadillo_matrix_Test, solve_armadillo_matrix_Success)
{
    // Arrange.
    static constexpr size_t dimension {3};
    munkres_cpp::matrix_armadillo<double> etalon_armadillo_matrix (dimension, dimension);
    //  {-1.0,  0.0, -1.0},
    //  { 0.0, -1.0, -1.0},
    //  {-1.0, -1.0,  0.0}
    etalon_armadillo_matrix (0, 0) = 1.0; etalon_armadillo_matrix (0, 1) = 0.0; etalon_armadillo_matrix (0, 2) = 1.0;
    etalon_armadillo_matrix (1, 0) = 0.0; etalon_armadillo_matrix (1, 1) = 1.0; etalon_armadillo_matrix (1, 2) = 1.0;
    etalon_armadillo_matrix (2, 0) = 1.0; etalon_armadillo_matrix (2, 1) = 1.0; etalon_armadillo_matrix (2, 2) = 0.0;

    munkres_cpp::matrix_armadillo<double> test_armadillo_matrix (dimension, dimension);
    //  {1.0,  0.0,  1.0},
    //  {0.0,  1.0,  1.0},
    //  {1.0,  1.0,  0.0}
    test_armadillo_matrix (0, 0) = 9.0; test_armadillo_matrix (0, 1) = 0.0; test_armadillo_matrix (0, 2) = 9.0;
    test_armadillo_matrix (1, 0) = 0.0; test_armadillo_matrix (1, 1) = 9.0; test_armadillo_matrix (1, 2) = 9.0;
    test_armadillo_matrix (2, 0) = 9.0; test_armadillo_matrix (2, 1) = 9.0; test_armadillo_matrix (2, 2) = 0.0;

    // Act.
    munkres_cpp::Munkres<double> solver;
    solver.solve (test_armadillo_matrix);

    // Assert.
    for (unsigned int row = 0; row < dimension; ++row) {
        for (unsigned int col = 0; col < dimension; ++col) {
            EXPECT_EQ ( etalon_armadillo_matrix (row, col), test_armadillo_matrix (row, col) );
        }
    }
}

