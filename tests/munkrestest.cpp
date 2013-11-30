#include <gtest/gtest.h>
#include "munkres.h"
#include "matrix.h"



class MunkresTest : public ::testing::Test
{
    protected:
        virtual void SetUp    ();
        virtual void TearDown ();

        Matrix <double> generateRandomMatrix    (const int, const int);
        void            isSingleSolution        (Matrix <double> &);
        void            isValidOutput           (Matrix <double> &);
        bool            isMatrixEqual           (Matrix <double> &, Matrix <double> &);
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



bool MunkresTest::isMatrixEqual (Matrix <double> & a, Matrix <double> & b)
{
    if (a.rows () != b.rows () || a.columns () != b.columns () )
        return false;

    for (unsigned int row = 0; row < a.rows (); ++row)
        for (unsigned int col = 0; col < a.columns (); ++col)
            if (a (row, col) != b (row, col) )
                return false;


    return true;
}



TEST_F (MunkresTest, solve_5x5_IsSingleSolution_Success)
{
    // Arrange.
    Matrix<double> mat = generateRandomMatrix(5, 5);
    Munkres m;

    // Act.
    m.solve(mat);

    // Assert.
    isSingleSolution(mat);
}



TEST_F (MunkresTest, solve_10x10_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> mat = generateRandomMatrix(10, 10);
  Munkres m;

    // Act.
  m.solve(mat);

    // Assert.
  isSingleSolution(mat);
}



TEST_F (MunkresTest, solve_50x50_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> mat = generateRandomMatrix(50, 50);
  Munkres m;

    // Act.
  m.solve(mat);

    // Assert.
  isSingleSolution(mat);
}



TEST_F (MunkresTest, solve_100x100_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> mat = generateRandomMatrix(100, 100);
  Munkres m;

    // Act.
  m.solve(mat);

    // Assert.
  isSingleSolution(mat);
}



TEST_F (MunkresTest, solve_200x200_IsSingleSolution_Success)
{
    // Arrange.
  Matrix<double> mat = generateRandomMatrix(200, 200);
  Munkres m;

    // Act.
  m.solve(mat);

    // Assert.
  isSingleSolution(mat);
}



TEST_F (MunkresTest, solve_10x10_IsValideOutput_Success)
{
  // Arrange.
  Matrix<double> mat = generateRandomMatrix(10, 10);
  Munkres m;

  // Act.
  m.solve(mat);

  // Assert.
  isValidOutput (mat);
}



TEST_F (MunkresTest, solve_3x3_IsValide_Success)
{
  // Arrange.
  // - + -
  // + - -
  // - - +
  Matrix<double> etalon_matrix{
    {-1.0,  0.0, -1.0},
    { 0.0, -1.0, -1.0},
    {-1.0, -1.0,  0.0}
  };
  // 1 0 1
  // 0 1 1
  // 1 1 0
  Matrix<double> test_matrix{
    {1.0,  0.0,  1.0},
    {0.0,  1.0,  1.0},
    {1.0,  1.0,  0.0}
  };

  Munkres m;

  // Act.
  m.solve(test_matrix);

  // Assert.
  EXPECT_TRUE (isMatrixEqual (test_matrix, etalon_matrix) );
}



TEST_F (MunkresTest, solve_3x3_IsValide_Fail)
{
  // Arrange.
  // + - -
  // + - -
  // - - +
  Matrix <double> etalon_matrix (3, 3);
  etalon_matrix (0, 0) =  0.0;    // Wrong.
  etalon_matrix (0, 1) = -1.0;    // Wrong.
  etalon_matrix (0, 2) = -1.0;
  etalon_matrix (1, 0) =  0.0;
  etalon_matrix (1, 1) = -1.0;
  etalon_matrix (1, 2) = -1.0;
  etalon_matrix (2, 0) = -1.0;
  etalon_matrix (2, 1) = -1.0;
  etalon_matrix (2, 2) =  0.0;
  // 1 0 1
  // 0 1 1
  // 1 1 0
  Matrix <double> test_matrix (3, 3);
  test_matrix (0, 0) = 1.0;
  test_matrix (0, 1) = 0.0;
  test_matrix (0, 2) = 1.0;
  test_matrix (1, 0) = 0.0;
  test_matrix (1, 1) = 1.0;
  test_matrix (1, 2) = 1.0;
  test_matrix (2, 0) = 1.0;
  test_matrix (2, 1) = 1.0;
  test_matrix (2, 2) = 0.0;

  Munkres m;

  // Act.
  m.solve(test_matrix);

  // Assert.
  EXPECT_FALSE (isMatrixEqual (test_matrix, etalon_matrix) );
}
