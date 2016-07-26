#include <gtest/gtest.h>
#include "adapters/std_2d_array.h"
#include <iostream>
#include <iomanip>



class Adapters_std_2d_array_Test : public ::testing::Test
{
};



TEST_F (Adapters_std_2d_array_Test, convert_std_2d_array_to_munkres_matrix_Success)
{
    // Arrange.
    constexpr unsigned int dimension {3};
    const std::array<std::array<double, dimension>, dimension> test_array {{
                                                                               {1, 2, 3},
                                                                               {4, 5, 6},
                                                                               {7, 8, 9}
                                                                           }};
    const Matrix<double> etalon_matrix {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Act.
    const auto test_matrix = convert_std_2d_array_to_munkres_matrix<double, test_array.size ()>(test_array);

    // Assert.
    for (unsigned int row = 0; row < dimension; ++row) {
        for (unsigned int col = 0; col < dimension; ++col) {
            EXPECT_EQ ( etalon_matrix (row, col), test_matrix (row, col) );
        }
    }
}



TEST_F (Adapters_std_2d_array_Test, fill_std_2d_array_from_munkres_matrix_Success)
{
    // Arrange.
    constexpr unsigned int dimension {3};
    std::array<std::array<double, dimension>, dimension> test_array {{
                                                                         {0, 0, 0},
                                                                         {0, 0, 0},
                                                                         {0, 0, 0}
                                                                     }};
    const std::array<std::array<double, dimension>, dimension> etalon_array {{
                                                                                 {1, 2, 3},
                                                                                 {4, 5, 6},
                                                                                 {7, 8, 9}
                                                                             }};
    const Matrix<double> etalon_matrix {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Act.
    fill_std_2d_array_from_munkres_matrix<double, dimension>(test_array, etalon_matrix);

    // Assert.
    for (unsigned int row = 0; row < dimension; ++row) {
        for (unsigned int col = 0; col < dimension; ++col) {
            EXPECT_EQ (etalon_array [row][col], test_array [row][col]);
        }
    }
}



TEST_F (Adapters_std_2d_array_Test, solve_std_2d_array_Success)
{
    // Arrange.
    constexpr unsigned int dimension {3};
    std::array<std::array<double, dimension>, dimension> etalon_array {{
                                                                           {-1.0,  0.0, -1.0},
                                                                           { 0.0, -1.0, -1.0},
                                                                           {-1.0, -1.0,  0.0}
                                                                       }};
    std::array<std::array<double, dimension>, dimension> test_array {{
                                                                         {1.0,  0.0,  1.0},
                                                                         {0.0,  1.0,  1.0},
                                                                         {1.0,  1.0,  0.0}
                                                                     }};

    // Act.
    solve<double, dimension>(test_array);

    // Assert.
    for (unsigned int row = 0; row < dimension; ++row) {
        for (unsigned int col = 0; col < dimension; ++col) {
            EXPECT_EQ (etalon_array [row][col], test_array [row][col]);
        }
    }
}
