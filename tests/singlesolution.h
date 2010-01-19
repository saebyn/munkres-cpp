#include <cxxtest/TestSuite.h>

#include "../munkres.h"

class SingleSolutionTestSuite : public CxxTest::TestSuite {
public:
	void testSingleSolution5by5( void ) {
		for ( int i = 0 ; i < 10 ; i++ ) {
			Matrix<double> mat = generateRandomMatrix(5, 5);
			Munkres m;
			m.solve(mat);
			isSingleSolution(mat);
		}
	}

	void testSingleSolution10by10( void ) {
		for ( int i = 0 ; i < 10 ; i++ ) {
			Matrix<double> mat = generateRandomMatrix(10, 10);
			Munkres m;
			m.solve(mat);
			isSingleSolution(mat);
		}
	}

	void testSingleSolution50by50( void ) {
		for ( int i = 0 ; i < 10 ; i++ ) {
			Matrix<double> mat = generateRandomMatrix(50, 50);
			Munkres m;
			m.solve(mat);
			isSingleSolution(mat);
		}
	}

	void testSingleSolution100by100( void ) {
		for ( int i = 0 ; i < 10 ; i++ ) {
			Matrix<double> mat = generateRandomMatrix(100, 100);
			Munkres m;
			m.solve(mat);
			isSingleSolution(mat);
		}
	}

	void testSingleSolution200by200( void ) {
		for ( int i = 0 ; i < 10 ; i++ ) {
			Matrix<double> mat = generateRandomMatrix(200, 200);
			Munkres m;
			m.solve(mat);
			isSingleSolution(mat);
		}
	}
	
	void isSingleSolution(Matrix<double> matrix) {
		for ( int row = 0 ; row < matrix.rows() ; row++ ) {
			int columnsolutioncount = 0;
			for ( int col = 0 ; col < matrix.columns() ; col++ )
				if ( matrix(row,col) == 0 )
					columnsolutioncount++;

					
			TS_ASSERT_EQUALS ( columnsolutioncount, 1 );
		}

		for ( int col = 0 ; col < matrix.columns() ; col++ ) {
			int rowsolutioncount = 0;
			for ( int row = 0 ; row < matrix.rows() ; row++ )
				if ( matrix(row,col) == 0 )
					rowsolutioncount++;
					
			TS_ASSERT_EQUALS ( rowsolutioncount, 1 );
		}
	}
	
	Matrix<double> generateRandomMatrix(int nrows, int ncols) {
		Matrix<double> matrix(nrows, ncols);
	
		srandom(time(NULL)); // Seed random number generator.

		// Initialize matrix with random values.
		for ( int row = 0 ; row < matrix.rows() ; row++ )
			for ( int col = 0 ; col < matrix.columns() ; col++ )
				matrix(row,col) = (double)random();
		
		return matrix;
	}
};

