#include <gtest/gtest.h>
#include "munkres.h"
#include "matrix.h"
#include <iostream>
#include <iomanip>



// Forward declaration.
void replace_infinites(Matrix<double> &matrix);
void minimize_along_direction(Matrix<double> &matrix, bool over_columns);



class MunkresTest : public ::testing::Test
{
    protected:
        virtual void SetUp    ();
        virtual void TearDown ();

        Matrix <double> generateRandomMatrix    (const int, const int);
        void            isSingleSolution        (Matrix <double> &);
        void            isValidOutput           (Matrix <double> &);
        bool            isMatrixEqual           (Matrix <double> &, Matrix <double> &, bool);
        void            displayMatrix           (Matrix <double> &);
};



void MunkresTest::SetUp ()
{
}



void MunkresTest::TearDown ()
{
}



Matrix<double> MunkresTest::generateRandomMatrix(const int nrows, const int ncols)
{
  Matrix<double> matrix(nrows, ncols);

  srandom(time(NULL)); // Seed random number generator.

  // Initialize matrix with random values.
  for ( unsigned int row = 0 ; row < matrix.rows() ; row++ )
    for ( unsigned int col = 0 ; col < matrix.columns() ; col++ )
      matrix(row,col) = (double)random();

  return matrix;
}



void MunkresTest::isSingleSolution (Matrix <double> & matrix)
{
  for ( unsigned int row = 0 ; row < matrix.rows() ; row++ ) {
    int columnsolutioncount = 0;
    for ( unsigned int col = 0 ; col < matrix.columns() ; col++ )
      if ( matrix(row,col) == 0 )
        columnsolutioncount++;
    EXPECT_EQ ( columnsolutioncount, 1 );
  }

  for ( unsigned int col = 0 ; col < matrix.columns() ; col++ ) {
    int rowsolutioncount = 0;
    for ( unsigned int row = 0 ; row < matrix.rows() ; row++ )
      if ( matrix(row,col) == 0 )
        rowsolutioncount++;
    EXPECT_EQ ( rowsolutioncount, 1 );
  }
}



void MunkresTest::isValidOutput (Matrix <double> & matrix)
{
  for ( unsigned int row = 0 ; row < matrix.rows() ; row++ )
    for ( unsigned int col = 0 ; col < matrix.columns() ; col++ )
      EXPECT_TRUE ( matrix(row,col) == 0 || matrix(row,col) == -1 );
}



bool MunkresTest::isMatrixEqual (Matrix <double> & a, Matrix <double> & b, bool isOutputIfNotEqual = true)
{
    if (a.rows () != b.rows () || a.columns () != b.columns () ) {
        return false;
    }

    for (unsigned int row = 0; row < a.rows (); ++row) {
        for (unsigned int col = 0; col < a.columns (); ++col) {
            if (a (row, col) != b (row, col) ) {
                if (isOutputIfNotEqual) {
                    displayMatrix (a);
                    displayMatrix (b);
                }
                return false;
            }
        }
    }

    return true;
}



void MunkresTest::displayMatrix (Matrix <double> & matrix)
{
    const std::string indent ("           ");
    for (unsigned int row = 0; row < matrix.rows (); ++row) {
        std::cout << indent;
        for (unsigned int col = 0; col < matrix.columns (); ++col) {
            std::cout << std::setw (4) << std::setfill (' ') <<  matrix (row, col) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



TEST_F (MunkresTest, replace_infinites_4x4Case001_Success)
{
  // Arrange.
  const auto infinity = std::numeric_limits<double>::infinity();
  Matrix<double> etalon_matrix{
    { 1.0,      0.0,      3.0,      2.0},
    { 3.0,     -2.0,     -1.0,      0.0},
    {-1.0,      3.0,      2.0,      0.0},
    {-1.0,      0.0,      2.0,      3.0}
  };
  Matrix<double> test_matrix{
    { 1.0,      0.0,     infinity,  2.0},
    {infinity, -2.0,     -1.0,      0.0},
    {-1.0,     infinity,  2.0,      0.0},
    {-1.0,      0.0,      2.0, infinity}
  };

  // Act.
  replace_infinites (test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, replace_infinites_4x4Case002_Success)
{
  // Arrange.
  const auto infinity = std::numeric_limits<double>::infinity();
  Matrix<double> etalon_matrix{
    { 3.0,      0.0,      3.0,      2.0},
    { 3.0,     -2.0,     -1.0,      3.0},
    {-1.0,      3.0,      2.0,      3.0},
    {-1.0,      3.0,      2.0,      3.0}
  };
  Matrix<double> test_matrix{
    {infinity,  0.0,     infinity,  2.0},
    {infinity, -2.0,     -1.0, infinity},
    {-1.0,     infinity,  2.0, infinity},
    {-1.0,     infinity,  2.0, infinity}
  };

  // Act.
  replace_infinites (test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, replace_infinites_4x4Case003_Success)
{
  // Arrange.
  const auto infinity = std::numeric_limits<double>::infinity();
  Matrix<double> etalon_matrix{
    {-5.0,     -4.0,     -1.0,     -2.0},
    {-1.0,     -2.0,     -5.0,     -4.0},
    {-5.0,     -1.0,     -2.0,     -4.0},
    {-5.0,     -4.0,     -2.0,     -1.0}
  };
  Matrix<double> test_matrix{
    {-5.0,     -4.0,     infinity, -2.0},
    {infinity, -2.0,     -5.0,     -4.0},
    {-5.0,     infinity, -2.0,     -4.0},
    {-5.0,     -4.0,     -2.0, infinity}
  };

  // Act.
  replace_infinites (test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, replace_infinites_4x4Case004_Success)
{
  // Arrange.
  const auto infinity = std::numeric_limits<double>::infinity();
  Matrix<double> etalon_matrix{
    { 1.0,      0.0,      3.0,      2.0},
    { 3.0,     -2.0,     -1.0,      0.0},
    {-1.0,      3.0,      0.0,      0.0},
    {-1.0,      0.0,      0.0,      3.0}
  };
  Matrix<double> test_matrix{
    { 1.0,      0.0,     infinity,  2.0},
    {infinity, -2.0,     -1.0,      0.0},
    {-1.0,     infinity,  0.0,      0.0},
    {-1.0,      0.0,      0.0, infinity}
  };

  // Act.
  replace_infinites (test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}




TEST_F (MunkresTest, minimize_along_direction_5x5_OverRowsOnly_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    { 1.0,  0.0,  3.0,  2.0,  4.0},
    { 3.0, -2.0, -1.0,  0.0,  4.0},
    {-1.0,  3.0,  2.0,  1.0,  2.0},
    { 0.0,  2.0,  1.0,  0.0,  3.0},
    { 0.0,  1.0,  1.0,  0.0,  2.0}
  };
  Matrix<double> test_matrix{
    { 1.0,  0.0,  3.0,  2.0,  4.0},
    { 3.0, -2.0, -1.0,  0.0,  4.0},
    {-1.0,  3.0,  2.0,  1.0,  2.0},
    { 1.0,  3.0,  2.0,  1.0,  4.0},
    { 2.0,  3.0,  3.0,  2.0,  4.0}
  };

  // Act.
  minimize_along_direction(test_matrix, false);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, minimize_along_direction_5x5_OverRowsAndColumns_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    { 1.0,  0.0,  3.0,  2.0,  2.0},
    { 3.0, -2.0, -1.0,  0.0,  2.0},
    {-1.0,  3.0,  2.0,  1.0,  0.0},
    { 0.0,  2.0,  1.0,  0.0,  1.0},
    { 0.0,  1.0,  1.0,  0.0,  0.0}
  };
  Matrix<double> test_matrix{
    { 1.0,  0.0,  3.0,  2.0,  4.0},
    { 3.0, -2.0, -1.0,  0.0,  4.0},
    {-1.0,  3.0,  2.0,  1.0,  2.0},
    { 1.0,  3.0,  2.0,  1.0,  4.0},
    { 2.0,  3.0,  3.0,  2.0,  4.0}
  };

  // Act.
  minimize_along_direction(test_matrix, true);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, solve_5x5_IsSingleSolution_Success)
{
    // Arrange.
    Matrix<double> matrix = generateRandomMatrix(5, 5);
    Munkres munkres;

    // Act.
    munkres.solve(matrix);

    // Assert.
    isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_10x10_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> matrix = generateRandomMatrix(10, 10);
  Munkres munkres;

    // Act.
  munkres.solve(matrix);

    // Assert.
  isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_50x50_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> matrix = generateRandomMatrix(50, 50);
  Munkres munkres;

    // Act.
  munkres.solve(matrix);

    // Assert.
  isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_100x100_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> matrix = generateRandomMatrix(100, 100);
  Munkres munkres;

    // Act.
  munkres.solve(matrix);

    // Assert.
  isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_200x200_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> matrix = generateRandomMatrix(200, 200);
  Munkres munkres;

    // Act.
  munkres.solve(matrix);

    // Assert.
  isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_10x10_IsValideOutput_Success)
{
  // Arrange.
  Matrix<double> matrix = generateRandomMatrix(10, 10);
  Munkres munkres;

  // Act.
  munkres.solve(matrix);

  // Assert.
  isValidOutput (matrix);
}



TEST_F (MunkresTest, solve_1x1_ObviousSolution_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {0.0}
  };
  Matrix<double> test_matrix{
    {0.0}
  };

  Munkres munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, solve_2x2_ObviousSolution_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0,  0.0},
    { 0.0, -1.0}
  };
  Matrix<double> test_matrix{
    {1.0,  0.0},
    {0.0,  1.0}
  };

  Munkres munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, solve_3x3_ObviousSolution_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0,  0.0, -1.0},
    { 0.0, -1.0, -1.0},
    {-1.0, -1.0,  0.0}
  };
  Matrix<double> test_matrix{
    {1.0,  0.0,  1.0},
    {0.0,  1.0,  1.0},
    {1.0,  1.0,  0.0}
  };

  Munkres munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, solve_3x2_NonObviousSolutionCase001_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0,  0.0},
    { 0.0, -1.0},
    {-1.0, -1.0}
  };
  Matrix<double> test_matrix{
    {1.0,  2.0},
    {0.0,  9.0},
    {9.0,  9.0}
  };

  Munkres munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, solve_3x3_NonObviousSolutionCase001_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0,  0.0, -1.0},
    { 0.0, -1.0, -1.0},
    {-1.0, -1.0,  0.0}
  };
  Matrix<double> test_matrix{
    {1.0,  2.0,  1.0},
    {0.0,  9.0,  9.0},
    {9.0,  9.0,  0.0}
  };

  Munkres munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, solve_3x3_NonObviousSolutionCase002_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0, -1.0,  0.0},
    {-1.0,  0.0, -1.0},
    { 0.0, -1.0, -1.0}
  };
  Matrix<double> test_matrix{
    {0.0,  0.0,  4.0},
    {4.0,  3.0,  9.0},
    {3.0,  4.0,  9.0}
  };

  Munkres munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, solve_3x3_IsValide_Fail)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    { 0.0, -1.0, -1.0},
    //  ^     ^
    //  |     |
    // Wrong Wrong
    { 0.0, -1.0, -1.0},
    {-1.0, -1.0,  0.0}
  };
  Matrix<double> test_matrix{
    {1.0,  0.0,  1.0},
    {0.0,  1.0,  1.0},
    {1.0,  1.0,  0.0}
  };

  Munkres munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_FALSE (isMatrixEqual (test_matrix, etalon_matrix, false) );
}
