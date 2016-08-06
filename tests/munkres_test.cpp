#include <gtest/gtest.h>
#include "munkres-cpp/munkres.h"
#include "matrix_test.h"



template <typename T>
class MunkresTestAll : public ::testing::Test
{
    protected:
        munkres_cpp::Matrix<T> generateRandomMatrix (const int nrows, const int ncols)
        {
            munkres_cpp::Matrix<T> matrix (nrows, ncols);

            srandom ( time (nullptr) ); // Seed random number generator.

            // Initialize matrix with random values.
            for (unsigned int row = 0; row < matrix.rows (); row++)
                for (unsigned int col = 0; col < matrix.columns (); col++)
                    matrix (row,col) = static_cast <T> (random () );

            return matrix;
        }

        void isSingleSolution (munkres_cpp::Matrix<T> & matrix)
        {
            for (unsigned int row = 0; row < matrix.rows (); row++) {
                int columnsolutioncount = 0;
                for (unsigned int col = 0; col < matrix.columns (); col++)
                    if (matrix (row,col) == 0)
                        columnsolutioncount++;
                EXPECT_EQ ( columnsolutioncount, 1 );
            }

            for (unsigned int col = 0; col < matrix.columns (); col++) {
                int rowsolutioncount = 0;
                for (unsigned int row = 0; row < matrix.rows (); row++)
                    if (matrix (row,col) == 0)
                        rowsolutioncount++;
                EXPECT_EQ ( rowsolutioncount, 1 );
            }
        }

        void isValidOutput (munkres_cpp::Matrix<T> & matrix)
        {
            for (unsigned int row = 0; row < matrix.rows (); row++)
                for (unsigned int col = 0; col < matrix.columns (); col++)
                    EXPECT_TRUE ( matrix (row,col) == 0 || matrix (row,col) == -1 );
        }
};

typedef ::testing::Types <
    signed                  char
  , unsigned                char
  , signed      short       int
  , unsigned    short       int
  , signed                  int
  , unsigned                int
  , signed      long        int
  , unsigned    long        int
  , signed      long long   int
  , unsigned    long long   int
  , float
  , double
  , long double> TypesAll;

TYPED_TEST_CASE (MunkresTestAll, TypesAll);



template <typename T>
class MunkresTestFloating : public ::testing::Test
{
};

typedef ::testing::Types <
    float
  , double
  , long double> TypesFloating;

TYPED_TEST_CASE (MunkresTestFloating, TypesFloating);



template <typename T>
class MunkresTestFloatingLong : public ::testing::Test
{
};

typedef ::testing::Types <
    double
  , long double> TypesFloatingLong;

TYPED_TEST_CASE (MunkresTestFloatingLong, TypesFloatingLong);



TYPED_TEST (MunkresTestFloating, replace_infinites_4x4Case001_Success)
{
    // Arrange.
    const auto infinity = std::numeric_limits<TypeParam>::infinity ();
    Matrix<TypeParam> etalon_matrix {
        { 1.0,      0.0,      3.0,      2.0},
        { 3.0,     -2.0,     -1.0,      0.0},
        {-1.0,      3.0,      2.0,      0.0},
        {-1.0,      0.0,      2.0,      3.0}
    };
    Matrix<TypeParam> test_matrix {
        { 1.0,      0.0,     infinity,  2.0l},
        {infinity, -2.0,     -1.0l,     0.0l},
        {-1.0,     infinity,  2.0l,     0.0l},
        {-1.0,      0.0,      2.0l, infinity}
    };

    // Act.
    munkres_cpp::replace_infinites (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestFloating, replace_infinites_4x4Case002_Success)
{
    // Arrange.
    const auto infinity = std::numeric_limits<TypeParam>::infinity ();
    Matrix<TypeParam> etalon_matrix {
        { 3.0,      0.0,      3.0,      2.0},
        { 3.0,     -2.0,     -1.0,      3.0},
        {-1.0,      3.0,      2.0,      3.0},
        {-1.0,      3.0,      2.0,      3.0}
    };
    Matrix<TypeParam> test_matrix {
        {infinity,  0.0,     infinity,  2.0},
        {infinity, -2.0,     -1.0, infinity},
        {-1.0,     infinity,  2.0, infinity},
        {-1.0,     infinity,  2.0, infinity}
    };

    // Act.
    munkres_cpp::replace_infinites (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestFloating, replace_infinites_4x4Case003_Success)
{
    // Arrange.
    const auto infinity = std::numeric_limits<TypeParam>::infinity ();
    Matrix<TypeParam> etalon_matrix {
        {-5.0,     -4.0,     -1.0,     -2.0},
        {-1.0,     -2.0,     -5.0,     -4.0},
        {-5.0,     -1.0,     -2.0,     -4.0},
        {-5.0,     -4.0,     -2.0,     -1.0}
    };
    Matrix<TypeParam> test_matrix {
        {-5.0,     -4.0,     infinity, -2.0},
        {infinity, -2.0,     -5.0,     -4.0},
        {-5.0,     infinity, -2.0,     -4.0},
        {-5.0,     -4.0,     -2.0, infinity}
    };

    // Act.
    munkres_cpp::replace_infinites (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestFloating, replace_infinites_4x4Case004_Success)
{
    // Arrange.
    const auto infinity = std::numeric_limits<TypeParam>::infinity ();
    Matrix<TypeParam> etalon_matrix {
        { 1.0,      0.0,      3.0,      2.0},
        { 3.0,     -2.0,     -1.0,      0.0},
        {-1.0,      3.0,      0.0,      0.0},
        {-1.0,      0.0,      0.0,      3.0}
    };
    Matrix<TypeParam> test_matrix {
        { 1.0,      0.0,     infinity,  2.0},
        {infinity, -2.0,     -1.0,      0.0},
        {-1.0,     infinity,  0.0,      0.0},
        {-1.0,      0.0,      0.0, infinity}
    };

    // Act.
    munkres_cpp::replace_infinites (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestFloating, replace_infinites_4x4Case005_Success)
{
    // Arrange.
    const auto infinity = std::numeric_limits<TypeParam>::infinity ();
    Matrix<TypeParam> etalon_matrix {
        {     0.0,      0.0,      0.0,      0.0},
        {     0.0,      0.0,      0.0,      0.0},
        {     0.0,      0.0,      0.0,      0.0},
        {     0.0,      0.0,      0.0,      0.0}
    };
    Matrix<TypeParam> test_matrix {
        {infinity, infinity, infinity, infinity},
        {infinity, infinity, infinity, infinity},
        {infinity, infinity, infinity, infinity},
        {infinity, infinity, infinity, infinity}
    };

    // Act.
    munkres_cpp::replace_infinites (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestAll, minimize_along_direction_5x5_OverRowsOnly_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        { 1.0,  0.0,  3.0,  2.0,  4.0},
        { 3.0, -2.0, -1.0,  0.0,  4.0},
        {-1.0,  3.0,  2.0,  1.0,  2.0},
        { 0.0,  2.0,  1.0,  0.0,  3.0},
        { 0.0,  1.0,  1.0,  0.0,  2.0}
    };
    Matrix<TypeParam> test_matrix {
        { 1.0,  0.0,  3.0,  2.0,  4.0},
        { 3.0, -2.0, -1.0,  0.0,  4.0},
        {-1.0,  3.0,  2.0,  1.0,  2.0},
        { 1.0,  3.0,  2.0,  1.0,  4.0},
        { 2.0,  3.0,  3.0,  2.0,  4.0}
    };

    // Act.
    munkres_cpp::minimize_along_direction (test_matrix, false);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestAll, minimize_along_direction_5x5_OverColumnsOnly_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        { 1.0,  0.0,  3.0,  2.0,  2.0},
        { 3.0, -2.0, -1.0,  0.0,  2.0},
        {-1.0,  3.0,  2.0,  1.0,  0.0},
        { 1.0,  3.0,  2.0,  1.0,  2.0},
        { 2.0,  3.0,  3.0,  2.0,  2.0}
    };
    Matrix<TypeParam> test_matrix {
        { 1.0,  0.0,  3.0,  2.0,  4.0},
        { 3.0, -2.0, -1.0,  0.0,  4.0},
        {-1.0,  3.0,  2.0,  1.0,  2.0},
        { 1.0,  3.0,  2.0,  1.0,  4.0},
        { 2.0,  3.0,  3.0,  2.0,  4.0}
    };

    // Act.
    munkres_cpp::minimize_along_direction (test_matrix, true);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestAll, minimize_along_direction_5x5_OverRowsAndColumns_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        { 1.0,  0.0,  3.0,  2.0,  2.0},
        { 3.0, -2.0, -1.0,  0.0,  2.0},
        {-1.0,  3.0,  2.0,  1.0,  0.0},
        { 0.0,  2.0,  1.0,  0.0,  1.0},
        { 0.0,  1.0,  1.0,  0.0,  0.0}
    };
    Matrix<TypeParam> test_matrix {
        { 1.0,  0.0,  3.0,  2.0,  4.0},
        { 3.0, -2.0, -1.0,  0.0,  4.0},
        {-1.0,  3.0,  2.0,  1.0,  2.0},
        { 1.0,  3.0,  2.0,  1.0,  4.0},
        { 2.0,  3.0,  3.0,  2.0,  4.0}
    };

    // Act.
    munkres_cpp::minimize_along_direction (test_matrix, false);
    munkres_cpp::minimize_along_direction (test_matrix, true);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestAll, solve_5x5_IsSingleSolution_Success)
{
    // Arrange.
    munkres_cpp::Matrix<TypeParam> matrix = this->generateRandomMatrix (5, 5);
    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (matrix);

    // Assert.
    this->isSingleSolution (matrix);
}



TYPED_TEST (MunkresTestAll, solve_10x10_IsSingleSolution_Success)
{
    // Arrange.
    munkres_cpp::Matrix<TypeParam> matrix = this->generateRandomMatrix (10, 10);
    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (matrix);

    // Assert.
    this->isSingleSolution (matrix);
}



TYPED_TEST (MunkresTestAll, solve_50x50_IsSingleSolution_Success)
{
    // Arrange.
    munkres_cpp::Matrix<TypeParam> matrix = this->generateRandomMatrix (50, 50);
    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (matrix);

    // Assert.
    this->isSingleSolution (matrix);
}



TYPED_TEST (MunkresTestAll, solve_100x100_IsSingleSolution_Success)
{
    // Arrange.
    munkres_cpp::Matrix<TypeParam> matrix = this->generateRandomMatrix (100, 100);
    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (matrix);

    // Assert.
    this->isSingleSolution (matrix);
}



TYPED_TEST (MunkresTestAll, solve_200x200_IsSingleSolution_Success)
{
    // Arrange.
    munkres_cpp::Matrix<TypeParam> matrix = this->generateRandomMatrix (200, 200);
    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (matrix);

    // Assert.
    this->isSingleSolution (matrix);
}



TYPED_TEST (MunkresTestAll, solve_10x10_IsValideOutput_Success)
{
    // Arrange.
    munkres_cpp::Matrix<TypeParam> matrix = this->generateRandomMatrix (10, 10);
    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (matrix);

    // Assert.
    this->isValidOutput (matrix);
}



TYPED_TEST (MunkresTestAll, solve_1x1_ObviousSolution_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {0.0}
    };
    Matrix<TypeParam> test_matrix {
        {0.0}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestAll, solve_2x2_ObviousSolution_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0,  0.0},
        { 0.0, -1.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.0,  0.0},
        {0.0,  1.0}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestAll, solve_3x3_ObviousSolution_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0,  0.0, -1.0},
        { 0.0, -1.0, -1.0},
        {-1.0, -1.0,  0.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.0,  0.0,  1.0},
        {0.0,  1.0,  1.0},
        {1.0,  1.0,  0.0}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestAll, solve_3x2_NonObviousSolutionCase001_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0,  0.0},
        { 0.0, -1.0},
        {-1.0, -1.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.0,  2.0},
        {0.0,  9.0},
        {9.0,  9.0}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



// This is simplified version of test case #008.
TYPED_TEST (MunkresTestFloating, solve_3x2_NonObviousSolutionCase002_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0, -1.0},
        { 0.0, -1.0},
        {-1.0,  0.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.0e+17, 3},
        {2,       1.0e+17},
        {4,       1}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



// This is simplified version of test case #009 (transposed version of test case 002).
TYPED_TEST (MunkresTestFloating, solve_2x3_NonObviousSolutionCase003_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0,  0.0, -1.0},
        {-1.0, -1.0,  0.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.0e+17, 2,       4},
        {3,       1.0e+17, 1}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



// This is test case based on test case #002, but extended by one "impossible" task and one "lazy" worker.
TYPED_TEST (MunkresTestFloating, solve_4x3_NonObviousSolutionCase004_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0, -1.0, -1.0},
        { 0.0, -1.0, -1.0},
        {-1.0, -1.0,  0.0},
        {-1.0,  0.0, -1.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.0e+17, 3,       1.0e+17},
        {2,       1.0e+17, 1.0e+17},
        {1.0e+17, 1.0e+17, 1.0e+17},
        {4,       1,       1.0e+17}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ ( etalon_matrix (1, 0), test_matrix (1, 0) );
    EXPECT_EQ ( etalon_matrix (3, 1), test_matrix (3, 1) );
}



// This is test case based on test case #003, but extended by one "impossible" task and one "lazy" worker.
TYPED_TEST (MunkresTestFloating, solve_3x4_NonObviousSolutionCase005_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0,  0.0, -1.0, -1.0},
        {-1.0, -1.0, -1.0,  0.0},
        {-1.0, -1.0,  0.0, -1.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.0e+17, 2,       1.0e17, 4},
        {3,       1.0e+17, 1.0e17, 1},
        {1.0e+17, 1.0e+17, 1.0e17, 1.0e+17}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ ( etalon_matrix (0, 1), test_matrix (0, 1) );
    EXPECT_EQ ( etalon_matrix (1, 3), test_matrix (1, 3) );
}



TYPED_TEST (MunkresTestAll, solve_3x3_NonObviousSolutionCase006_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0,  0.0, -1.0},
        { 0.0, -1.0, -1.0},
        {-1.0, -1.0,  0.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.0,  2.0,  1.0},
        {0.0,  9.0,  9.0},
        {9.0,  9.0,  0.0}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestAll, solve_3x3_NonObviousSolutionCase007_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0, -1.0,  0.0},
        {-1.0,  0.0, -1.0},
        { 0.0, -1.0, -1.0}
    };
    Matrix<TypeParam> test_matrix {
        {0.0,  0.0,  4.0},
        {4.0,  3.0,  9.0},
        {3.0,  4.0,  9.0}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}




TYPED_TEST (MunkresTestFloatingLong, solve_6x4_NonObviousSolutionCase008_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0, -1.0, -1.0, -1.0},
        { 0.0, -1.0, -1.0, -1.0},
        {-1.0,  0.0, -1.0, -1.0},
        {-1.0, -1.0, -1.0, -1.0},
        {-1.0, -1.0, -1.0,  0.0},
        {-1.0, -1.0,  0.0, -1.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.79769e+308, 7.33184e+08,  9.41561e+08,  2.79247e+08},
        {3.06449e+08,  1.79769e+308, 3.3464e+08,   7.06878e+08},
        {9.93296e+08,  1.9414e+08,   1.79769e+308, 1.14174e+08},
        {3.51623e+08,  2.48635e+08,  7.81242e+08,  1.79769e+308},
        {7.02639e+08,  8.51663e+08,  9.37382e+08,  4.96945e+07},
        {7.58851e+08,  8.58445e+08,  8.7235e+07,   5.47076e+08}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestFloatingLong, solve_4x6_NonObviousSolutionCase009_Success)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        {-1.0,  0.0, -1.0, -1.0, -1.0, -1.0},
        {-1.0, -1.0,  0.0, -1.0, -1.0, -1.0},
        {-1.0, -1.0, -1.0, -1.0, -1.0,  0.0},
        {-1.0, -1.0, -1.0, -1.0,  0.0, -1.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.79769e+308, 3.06449e+08,  9.93296e+08,  3.51623e+08,  7.02639e+08,  7.58851e+08},
        {7.33184e+08,  1.79769e+308, 1.9414e+08,   2.48635e+08,  8.51663e+08,  8.58445e+08},
        {9.41561e+08,  3.3464e+08,   1.79769e+308, 7.81242e+08,  9.37382e+08,  8.7235e+07},
        {2.79247e+08,  7.06878e+08,  1.14174e+08,  1.79769e+308, 4.96945e+07,  5.47076e+08}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_EQ (etalon_matrix, test_matrix);
}



TYPED_TEST (MunkresTestAll, solve_3x3_IsValide_Fail)
{
    // Arrange.
    Matrix<TypeParam> etalon_matrix {
        { 0.0, -1.0, -1.0},
        //  ^     ^
        //  |     |
        // Wrong Wrong
        { 0.0, -1.0, -1.0},
        {-1.0, -1.0,  0.0}
    };
    Matrix<TypeParam> test_matrix {
        {1.0,  0.0,  1.0},
        {0.0,  1.0,  1.0},
        {1.0,  1.0,  0.0}
    };

    munkres_cpp::Munkres<TypeParam> munkres;

    // Act.
    munkres.solve (test_matrix);

    // Assert.
    EXPECT_NE (etalon_matrix, test_matrix);
}

