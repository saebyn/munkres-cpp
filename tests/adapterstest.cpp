#include <gtest/gtest.h>
#include "adapters.h"
#include <iostream>
#include <iomanip>



class AdaptersTest : public ::testing::Test
{
};



TEST_F (AdaptersTest, convert_std_2d_array_to_munkres_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  const std::array <std::array <double, dimension>, dimension> test_array {{
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  }};
  const Matrix <double> etalon_matrix {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  // Act.
  const auto test_matrix = convert_std_2d_array_to_munkres_matrix <double, test_array.size ()> (test_array);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_matrix (row, col), test_matrix (row, col) );
    }
  }
}



TEST_F (AdaptersTest, fill_std_2d_array_from_munkres_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  std::array <std::array <double, dimension>, dimension> test_array {{
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  }};
  const std::array <std::array <double, dimension>, dimension> etalon_array {{
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  }};
  const Matrix <double> etalon_matrix {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  // Act.
  fill_std_2d_array_from_munkres_matrix <double, dimension> (test_array, etalon_matrix);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_array [row][col], test_array [row][col]);
    }
  }
}



TEST_F (AdaptersTest, solve_std_2d_array_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  std::array <std::array <double, dimension>, dimension> etalon_array{{
    {-1.0,  0.0, -1.0},
    { 0.0, -1.0, -1.0},
    {-1.0, -1.0,  0.0}
  }};
  std::array <std::array <double, dimension>, dimension> test_array{{
    {1.0,  0.0,  1.0},
    {0.0,  1.0,  1.0},
    {1.0,  1.0,  0.0}
  }};

  // Act.
  solve <dimension> (test_array);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_array [row][col], test_array [row][col]);
    }
  }
}



TEST_F (AdaptersTest, convert_raw_2d_array_to_munkres_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  const double test_array [dimension][dimension] {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };
  const Matrix <double> etalon_matrix {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  // Act.
  const auto test_matrix = convert_raw_2d_array_to_munkres_matrix <double, dimension> (test_array);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_matrix (row, col), test_matrix (row, col) );
    }
  }
}



TEST_F (AdaptersTest, fill_raw_2d_array_from_munkres_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  double test_array [dimension][dimension] {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  };
  const double etalon_array [dimension][dimension] {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };
  const Matrix <double> etalon_matrix {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  // Act.
  fill_raw_2d_array_from_munkres_matrix <double, dimension> (test_array, etalon_matrix);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_array [row][col], test_array [row][col]);
    }
  }
}



TEST_F (AdaptersTest, solve_raw_2d_array_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  double etalon_array [dimension][dimension]{
    {-1.0,  0.0, -1.0},
    { 0.0, -1.0, -1.0},
    {-1.0, -1.0,  0.0}
  };
  double test_array [dimension][dimension]{
    {1.0,  0.0,  1.0},
    {0.0,  1.0,  1.0},
    {1.0,  1.0,  0.0}
  };

  // Act.
  solve <dimension> (test_array);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_array [row][col], test_array [row][col]);
    }
  }
}