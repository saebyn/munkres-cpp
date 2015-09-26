#include <gtest/gtest.h>
#include "adapters/boostmatrixadapter.h"
#include <iostream>
#include <iomanip>



class Adapters_boost_matrix_Test : public ::testing::Test
{
};



TEST_F (Adapters_boost_matrix_Test, convert_boost_matrix_to_munkres_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  boost::numeric::ublas::matrix <double> test_boost_matrix (dimension, dimension);
  //  {1, 2, 3},
  //  {4, 5, 6},
  //  {7, 8, 9}
  test_boost_matrix (0, 0) = 1; test_boost_matrix (0, 1) = 2; test_boost_matrix (0, 2) = 3;
  test_boost_matrix (1, 0) = 4; test_boost_matrix (1, 1) = 5; test_boost_matrix (1, 2) = 6;
  test_boost_matrix (2, 0) = 7; test_boost_matrix (2, 1) = 8; test_boost_matrix (2, 2) = 9;
  const Matrix <double> etalon_matrix {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  BoostMatrixAdapter<double> adapter;

  // Act.
  const auto test_matrix = adapter.convertToMatrix(test_boost_matrix);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_matrix (row, col), test_matrix (row, col) );
    }
  }
}

TEST_F (Adapters_boost_matrix_Test, convert_non_square_boost_matrix_to_munkres_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension1 {2};
  constexpr unsigned int dimension2 {3};
  boost::numeric::ublas::matrix <double> test_boost_matrix (dimension1, dimension2);
  //  {1, 2, 3},
  //  {4, 5, 6}
  test_boost_matrix (0, 0) = 1; test_boost_matrix (0, 1) = 2; test_boost_matrix (0, 2) = 3;
  test_boost_matrix (1, 0) = 4; test_boost_matrix (1, 1) = 5; test_boost_matrix (1, 2) = 6;
  const Matrix <double> etalon_matrix {
    {1, 2, 3},
    {4, 5, 6}
  };

  BoostMatrixAdapter<double> adapter;

  // Act.
  const auto test_matrix = adapter.convertToMatrix(test_boost_matrix);

  // Assert.
  for (unsigned int row = 0; row < dimension1; ++row) {
    for (unsigned int col = 0; col < dimension2; ++col) {
      EXPECT_EQ (etalon_matrix (row, col), test_matrix (row, col) );
    }
  }
}

TEST_F (Adapters_boost_matrix_Test, fill_boost_matrix_from_munkres_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  boost::numeric::ublas::matrix <double> test_boost_matrix (dimension, dimension);
  //  {0, 0, 0},
  //  {0, 0, 0},
  //  {0, 0, 0}
  test_boost_matrix (0, 0) = 0; test_boost_matrix (0, 1) = 0; test_boost_matrix (0, 2) = 0;
  test_boost_matrix (1, 0) = 0; test_boost_matrix (1, 1) = 0; test_boost_matrix (1, 2) = 0;
  test_boost_matrix (2, 0) = 0; test_boost_matrix (2, 1) = 0; test_boost_matrix (2, 2) = 0;

  boost::numeric::ublas::matrix <double> etalon_boost_matrix (dimension, dimension);
  //  {1, 2, 3},
  //  {4, 5, 6},
  //  {7, 8, 9}
  etalon_boost_matrix (0, 0) = 1; etalon_boost_matrix (0, 1) = 2; etalon_boost_matrix (0, 2) = 3;
  etalon_boost_matrix (1, 0) = 4; etalon_boost_matrix (1, 1) = 5; etalon_boost_matrix (1, 2) = 6;
  etalon_boost_matrix (2, 0) = 7; etalon_boost_matrix (2, 1) = 8; etalon_boost_matrix (2, 2) = 9;

  const Matrix <double> etalon_matrix {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };

  BoostMatrixAdapter<double> adapter;

  // Act.
  adapter.convertFromMatrix(test_boost_matrix, etalon_matrix);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_boost_matrix (row, col), test_boost_matrix (row, col) );
    }
  }
}

TEST_F (Adapters_boost_matrix_Test, fill_non_square_boost_matrix_from_munkres_matrix_Success)
{
  // Arrange.
    constexpr unsigned int dimension1 {2};
    constexpr unsigned int dimension2 {3};
  boost::numeric::ublas::matrix <double> test_boost_matrix (dimension1, dimension2);
  //  {0, 0, 0},
  //  {0, 0, 0}
  test_boost_matrix (0, 0) = 0; test_boost_matrix (0, 1) = 0; test_boost_matrix (0, 2) = 0;
  test_boost_matrix (1, 0) = 0; test_boost_matrix (1, 1) = 0; test_boost_matrix (1, 2) = 0;

  boost::numeric::ublas::matrix <double> etalon_boost_matrix (dimension1, dimension2);
  //  {1, 2, 3},
  //  {4, 5, 6}
  etalon_boost_matrix (0, 0) = 1; etalon_boost_matrix (0, 1) = 2; etalon_boost_matrix (0, 2) = 3;
  etalon_boost_matrix (1, 0) = 4; etalon_boost_matrix (1, 1) = 5; etalon_boost_matrix (1, 2) = 6;

  const Matrix <double> etalon_matrix {
    {1, 2, 3},
    {4, 5, 6}
  };

  BoostMatrixAdapter<double> adapter;

  // Act.
  adapter.convertFromMatrix(test_boost_matrix, etalon_matrix);

  // Assert.
  for (unsigned int row = 0; row < dimension1; ++row) {
    for (unsigned int col = 0; col < dimension2; ++col) {
      EXPECT_EQ (etalon_boost_matrix (row, col), test_boost_matrix (row, col) );
    }
  }
}

TEST_F (Adapters_boost_matrix_Test, solve_boost_matrix_Success)
{
  // Arrange.
  constexpr unsigned int dimension {3};
  boost::numeric::ublas::matrix <double> etalon_boost_matrix (dimension, dimension);
  //  {-1.0,  0.0, -1.0},
  //  { 0.0, -1.0, -1.0},
  //  {-1.0, -1.0,  0.0}
  etalon_boost_matrix (0, 0) = -1.0; etalon_boost_matrix (0, 1) =  0.0; etalon_boost_matrix (0, 2) = -1.0;
  etalon_boost_matrix (1, 0) =  0.0; etalon_boost_matrix (1, 1) = -1.0; etalon_boost_matrix (1, 2) = -1.0;
  etalon_boost_matrix (2, 0) = -1.0; etalon_boost_matrix (2, 1) = -1.0; etalon_boost_matrix (2, 2) =  0.0;

  boost::numeric::ublas::matrix <double> test_boost_matrix (dimension, dimension);
  //  {1.0,  0.0,  1.0},
  //  {0.0,  1.0,  1.0},
  //  {1.0,  1.0,  0.0}
  test_boost_matrix (0, 0) = 1.0; test_boost_matrix (0, 1) = 0.0; test_boost_matrix (0, 2) = 1.0;
  test_boost_matrix (1, 0) = 0.0; test_boost_matrix (1, 1) = 1.0; test_boost_matrix (1, 2) = 1.0;
  test_boost_matrix (2, 0) = 1.0; test_boost_matrix (2, 1) = 1.0; test_boost_matrix (2, 2) = 0.0;

  BoostMatrixAdapter<double> adapter;

  // Act.
  adapter.solve(test_boost_matrix);

  // Assert.
  for (unsigned int row = 0; row < dimension; ++row) {
    for (unsigned int col = 0; col < dimension; ++col) {
      EXPECT_EQ (etalon_boost_matrix (row, col), test_boost_matrix (row, col) );
    }
  }
}
