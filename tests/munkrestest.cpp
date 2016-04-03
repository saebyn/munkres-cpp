#include <gtest/gtest.h>
#include "munkres.h"
#include "matrixtest.h"
#include <iostream>
#include <iomanip>

class MunkresTest : public ::testing::Test
{
    protected:
        virtual void SetUp    ();
        virtual void TearDown ();

        Matrix <double> generateRandomMatrix    (const int, const int);
        void            isSingleSolution        (Matrix <double> &);
        void            isValidOutput           (Matrix <double> &);
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

  srandom(time(nullptr)); // Seed random number generator.

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
  Munkres<double>::replace_infinites (test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
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
  Munkres<double>::replace_infinites(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
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
  Munkres<double>::replace_infinites (test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
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
  Munkres<double>::replace_infinites (test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MunkresTest, replace_infinites_4x4Case005_Success)
{
  // Arrange.
  const auto infinity = std::numeric_limits<double>::infinity();
  Matrix<double> etalon_matrix{
    {     0.0,      0.0,      0.0,      0.0},
    {     0.0,      0.0,      0.0,      0.0},
    {     0.0,      0.0,      0.0,      0.0},
    {     0.0,      0.0,      0.0,      0.0}
  };
  Matrix<double> test_matrix{
    {infinity, infinity, infinity, infinity},
    {infinity, infinity, infinity, infinity},
    {infinity, infinity, infinity, infinity},
    {infinity, infinity, infinity, infinity}
  };

  // Act.
  Munkres<double>::replace_infinites (test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
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
  Munkres<double>::minimize_along_direction(test_matrix, false);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MunkresTest, minimize_along_direction_5x5_OverColumnsOnly_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    { 1.0,  0.0,  3.0,  2.0,  2.0},
    { 3.0, -2.0, -1.0,  0.0,  2.0},
    {-1.0,  3.0,  2.0,  1.0,  0.0},
    { 1.0,  3.0,  2.0,  1.0,  2.0},
    { 2.0,  3.0,  3.0,  2.0,  2.0}
  };
  Matrix<double> test_matrix{
    { 1.0,  0.0,  3.0,  2.0,  4.0},
    { 3.0, -2.0, -1.0,  0.0,  4.0},
    {-1.0,  3.0,  2.0,  1.0,  2.0},
    { 1.0,  3.0,  2.0,  1.0,  4.0},
    { 2.0,  3.0,  3.0,  2.0,  4.0}
  };

  // Act.
  Munkres<double>::minimize_along_direction(test_matrix, true);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
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
  Munkres<double>::minimize_along_direction(test_matrix, false);
  Munkres<double>::minimize_along_direction(test_matrix, true);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MunkresTest, solve_5x5_IsSingleSolution_Success)
{
    // Arrange.
    Matrix<double> matrix = generateRandomMatrix(5, 5);
    Munkres<double> munkres;

    // Act.
    munkres.solve(matrix);

    // Assert.
    isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_10x10_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> matrix = generateRandomMatrix(10, 10);
  Munkres<double> munkres;

    // Act.
  munkres.solve(matrix);

    // Assert.
  isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_50x50_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> matrix = generateRandomMatrix(50, 50);
  Munkres<double> munkres;

    // Act.
  munkres.solve(matrix);

    // Assert.
  isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_100x100_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> matrix = generateRandomMatrix(100, 100);
  Munkres<double> munkres;

    // Act.
  munkres.solve(matrix);

    // Assert.
  isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_200x200_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> matrix = generateRandomMatrix(200, 200);
  Munkres<double> munkres;

    // Act.
  munkres.solve(matrix);

    // Assert.
  isSingleSolution(matrix);
}



TEST_F (MunkresTest, solve_10x10_IsValideOutput_Success)
{
  // Arrange.
  Matrix<double> matrix = generateRandomMatrix(10, 10);
  Munkres<double> munkres;

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

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
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

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
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

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
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

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



// This is simplified version of test case #008.
TEST_F (MunkresTest, solve_3x2_NonObviousSolutionCase002_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0, -1.0},
    { 0.0, -1.0},
    {-1.0,  0.0}
  };
  Matrix<double> test_matrix{
    {1.0e+17, 3},
    {2,       1.0e+17},
    {4,       1}
  };

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



// This is simplified version of test case #009 (transposed version of test case 002).
TEST_F (MunkresTest, solve_2x3_NonObviousSolutionCase003_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0,  0.0, -1.0},
    {-1.0, -1.0,  0.0}
  };
  Matrix<double> test_matrix{
    {1.0e+17, 2,       4},
    {3,       1.0e+17, 1}
  };

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



// This is test case based on test case #002, but extended by one "impossible" task and one "lazy" worker.
TEST_F (MunkresTest, solve_4x3_NonObviousSolutionCase004_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0, -1.0, -1.0},
    { 0.0, -1.0, -1.0},
    {-1.0, -1.0,  0.0},
    {-1.0,  0.0, -1.0}
  };
  Matrix<double> test_matrix{
    {1.0e+17, 3,       1.0e+17},
    {2,       1.0e+17, 1.0e+17},
    {1.0e+17, 1.0e+17, 1.0e+17},
    {4,       1,       1.0e+17}
  };

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix (1, 0), test_matrix (1, 0) );
  EXPECT_EQ (etalon_matrix (3, 1), test_matrix (3, 1) );
}



// This is test case based on test case #003, but extended by one "impossible" task and one "lazy" worker.
TEST_F (MunkresTest, solve_3x4_NonObviousSolutionCase005_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0,  0.0, -1.0, -1.0},
    {-1.0, -1.0, -1.0,  0.0},
    {-1.0, -1.0,  0.0, -1.0}
  };
  Matrix<double> test_matrix{
    {1.0e+17, 2,       1.0e17, 4},
    {3,       1.0e+17, 1.0e17, 1},
    {1.0e+17, 1.0e+17, 1.0e17, 1.0e+17}
  };

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix (0, 1), test_matrix (0, 1) );
  EXPECT_EQ (etalon_matrix (1, 3), test_matrix (1, 3) );
}



TEST_F (MunkresTest, solve_3x3_NonObviousSolutionCase006_Success)
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

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MunkresTest, solve_3x3_NonObviousSolutionCase007_Success)
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

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MunkresTest, solve_6x4_NonObviousSolutionCase008_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0, -1.0, -1.0, -1.0},
    { 0.0, -1.0, -1.0, -1.0},
    {-1.0,  0.0, -1.0, -1.0},
    {-1.0, -1.0, -1.0, -1.0},
    {-1.0, -1.0, -1.0,  0.0},
    {-1.0, -1.0,  0.0, -1.0}
  };
  Matrix<double> test_matrix{
    {1.79769e+308, 7.33184e+08,  9.41561e+08,  2.79247e+08},
    {3.06449e+08,  1.79769e+308, 3.3464e+08,   7.06878e+08},
    {9.93296e+08,  1.9414e+08,   1.79769e+308, 1.14174e+08},
    {3.51623e+08,  2.48635e+08,  7.81242e+08,  1.79769e+308},
    {7.02639e+08,  8.51663e+08,  9.37382e+08,  4.96945e+07},
    {7.58851e+08,  8.58445e+08,  8.7235e+07,   5.47076e+08}
  };

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MunkresTest, solve_4x6_NonObviousSolutionCase009_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {-1.0,  0.0, -1.0, -1.0, -1.0, -1.0},
    {-1.0, -1.0,  0.0, -1.0, -1.0, -1.0},
    {-1.0, -1.0, -1.0, -1.0, -1.0,  0.0},
    {-1.0, -1.0, -1.0, -1.0,  0.0, -1.0}
  };
  Matrix<double> test_matrix{
    {1.79769e+308, 3.06449e+08,  9.93296e+08,  3.51623e+08,  7.02639e+08,  7.58851e+08},
    {7.33184e+08,  1.79769e+308, 1.9414e+08,   2.48635e+08,  8.51663e+08,  8.58445e+08},
    {9.41561e+08,  3.3464e+08,   1.79769e+308, 7.81242e+08,  9.37382e+08,  8.7235e+07},
    {2.79247e+08,  7.06878e+08,  1.14174e+08,  1.79769e+308, 4.96945e+07,  5.47076e+08}
  };

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
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

  Munkres<double> munkres;

  // Act.
  munkres.solve(test_matrix);

  // Assert.
  EXPECT_NE (etalon_matrix, test_matrix);
}
