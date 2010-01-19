#include <cxxtest/TestSuite.h>

#include "../munkres.h"

class ValidSolutionTestSuite : public CxxTest::TestSuite {
public:
	void testValidSolution( void ) {
		const int nrows = 10;
		const int ncols = 10;
		Matrix<double> matrix(nrows, ncols);
	
		srandom(time(NULL)); // Seed random number generator.

		// Initialize matrix with random values.
		for ( int row = 0 ; row < matrix.rows() ; row++ )
			for ( int col = 0 ; col < matrix.columns() ; col++ )
				matrix(row,col) = (double)random();

		Munkres m;

		m.solve(matrix);
		
		for ( int row = 0 ; row < matrix.rows() ; row++ )
			for ( int col = 0 ; col < matrix.columns() ; col++ )
				TS_ASSERT ( matrix(row,col) == 0 || matrix(row,col) == -1 );
	}
};

