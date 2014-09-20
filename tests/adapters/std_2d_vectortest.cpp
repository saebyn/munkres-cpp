#include <gtest/gtest.h>
#include "adapters/std_2d_vector.h"



class Adapters_std_2d_vector_Test : public ::testing::Test
{
};



TEST_F (Adapters_std_2d_vector_Test, convert_std_2d_vector_to_munkres_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  const std::vector <std::vector <double> > test_vector {{
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
  const auto test_matrix = convert_std_2d_vector_to_munkres_matrix <double> (test_vector);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_matrix (row, col), test_matrix (row, col) );
    }
  }
}



TEST_F (Adapters_std_2d_vector_Test, fill_std_2d_vector_from_munkres_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  std::vector <std::vector <double> > test_vector {{
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  }};
  const std::vector <std::vector <double> > etalon_vector {{
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
  fill_std_2d_vector_from_munkres_matrix <double> (test_vector, etalon_matrix);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_vector [row][col], test_vector [row][col]);
    }
  }
}



TEST_F (Adapters_std_2d_vector_Test, solve_std_2d_vector_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  std::vector <std::vector <double> > etalon_vector {{
    {-1.0,  0.0, -1.0},
    { 0.0, -1.0, -1.0},
    {-1.0, -1.0,  0.0}
  }};
  std::vector <std::vector <double> > test_vector {{
    {1.0,  0.0,  1.0},
    {0.0,  1.0,  1.0},
    {1.0,  1.0,  0.0}
  }};

  // Act.
  solve (test_vector);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_vector [row][col], test_vector [row][col]);
    }
  }
}
