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
	for ( int row = 0 ; row < matrix.rows() ; row++ )
		for ( int col = 0 ; col < matrix.columns() ; col++ )
			matrix(row,col) = (double)random();

	return matrix;
}



void MunkresTest::isSingleSolution (Matrix <double> & matrix)
{
	for ( int row = 0 ; row < matrix.rows() ; row++ ) {
		int columnsolutioncount = 0;
		for ( int col = 0 ; col < matrix.columns() ; col++ )
			if ( matrix(row,col) == 0 )
				columnsolutioncount++;
		EXPECT_EQ ( columnsolutioncount, 1 );
	}

	for ( int col = 0 ; col < matrix.columns() ; col++ ) {
		int rowsolutioncount = 0;
		for ( int row = 0 ; row < matrix.rows() ; row++ )
			if ( matrix(row,col) == 0 )
				rowsolutioncount++;
		EXPECT_EQ ( rowsolutioncount, 1 );
	}
}



void MunkresTest::isValidOutput (Matrix <double> & matrix)
{
	for ( int row = 0 ; row < matrix.rows() ; row++ )
		for ( int col = 0 ; col < matrix.columns() ; col++ )
			EXPECT_TRUE ( matrix(row,col) == 0 || matrix(row,col) == -1 );
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
	const int nrows = 10;
	const int ncols = 10;
	Matrix<double> matrix(nrows, ncols);

	srandom(time(NULL)); // Seed random number generator.

	// Initialize matrix with random values.
	for ( int row = 0 ; row < matrix.rows() ; row++ )
		for ( int col = 0 ; col < matrix.columns() ; col++ )
			matrix(row,col) = (double)random();

    Munkres m;

    // Act.
    m.solve(matrix);

    // Assert.
    isValidOutput (matrix);
}
