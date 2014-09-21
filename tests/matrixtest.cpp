#include <gtest/gtest.h>
#include "matrixtest.h"
#include <iostream>
#include <iomanip>



class MatrixTest : public ::testing::Test
{
    protected:
        virtual void SetUp    ();
        virtual void TearDown ();
};



void MatrixTest::SetUp ()
{
}



void MatrixTest::TearDown ()
{
}



TEST_F (MatrixTest, resize_From1x1To2x2WithDefaultValueDefaulted_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {7.0, 0.0},
    {0.0, 0.0}
  };
  Matrix<double> test_matrix{
    {7.0}
  };

  // Act.
  test_matrix.resize (2, 2);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, resize_From1x1To5x5WithDefaultValueDefaulted_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {7.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0, 0.0}
  };
  Matrix<double> test_matrix{
    {7.0}
  };

  // Act.
  test_matrix.resize (5, 5);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, resize_From5x5To3x3WithDefaultValueDefaulted_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {0.0, 0.1, 0.2},
    {1.0, 1.1, 1.2},
    {2.0, 2.1, 2.2}
  };
  Matrix<double> test_matrix{
    {0.0, 0.1, 0.2, 0.3, 0.4},
    {1.0, 1.1, 1.2, 1.3, 1.4},
    {2.0, 2.1, 2.2, 2.3, 2.4},
    {3.0, 3.1, 3.2, 3.3, 3.4},
    {4.0, 4.1, 4.2, 4.3, 4.4}
  };

  // Act.
  test_matrix.resize (3, 3);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, resize_From2x2To4x4WithDefaultValueExplicit_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {0.0, 0.1, 9.9, 9.9},
    {1.0, 1.1, 9.9, 9.9},
    {9.9, 9.9, 9.9, 9.9},
    {9.9, 9.9, 9.9, 9.9}
  };
  Matrix<double> test_matrix{
    {0.0, 0.1},
    {1.0, 1.1}
  };

  // Act.
  test_matrix.resize (4, 4, 9.9);

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, clear_1x1_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {0.0}
  };
  Matrix<double> test_matrix{
    {7.0}
  };

  // Act.
  test_matrix.clear ();

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, clear_4x4_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0}
  };
  Matrix<double> test_matrix{
    {1.1, 1.2, 1.3, 1.4},
    {2.1, 2.2, 2.3, 2.4},
    {3.1, 3.2, 3.3, 3.4},
    {4.1, 4.2, 4.3, 4.4}
  };

  // Act.
  test_matrix.clear ();

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, operatorAssignment_0x0_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix {std::initializer_list <std::initializer_list <double> > () };
  Matrix<double> test_matrix{
    {0.0, 0.1, 0.2},
    {3.0, 3.1, 3.2},
    {4.0, 4.1, 4.2}
  };

  // Act.
  test_matrix = etalon_matrix;

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, operatorAssignment_3x3_Success)
{
  // Arrange.
  Matrix<double> etalon_matrix{
    {0.0, 0.1, 0.2},
    {1.0, 1.1, 1.2},
    {2.0, 2.1, 2.2}
  };
  Matrix<double> test_matrix;

  // Act.
  test_matrix = etalon_matrix;

  // Assert.
  EXPECT_EQ (etalon_matrix, test_matrix);
}



TEST_F (MatrixTest, operatorSubscript_Success)
{
  // Arrange.
  Matrix<double> test_matrix{
    {0.0, 0.1, 0.2},
    {1.0, 1.1, 1.2},
    {2.0, 2.1, 2.2}
  };

  // Act, Assert.
  EXPECT_FLOAT_EQ (0.0, test_matrix (0, 0) );
  EXPECT_FLOAT_EQ (0.1, test_matrix (0, 1) );
  EXPECT_FLOAT_EQ (0.2, test_matrix (0, 2) );
  EXPECT_FLOAT_EQ (1.0, test_matrix (1, 0) );
  EXPECT_FLOAT_EQ (1.1, test_matrix (1, 1) );
  EXPECT_FLOAT_EQ (1.2, test_matrix (1, 2) );
  EXPECT_FLOAT_EQ (2.0, test_matrix (2, 0) );
  EXPECT_FLOAT_EQ (2.1, test_matrix (2, 1) );
  EXPECT_FLOAT_EQ (2.2, test_matrix (2, 2) );
}



TEST_F (MatrixTest, max_1x1_Success)
{
  // Arrange.
  Matrix<double> test_matrix{
    {0.0}
  };
  constexpr double etalon_result {0.0};

  // Act.
  const double test_result = test_matrix.max ();

  // Assert.
  EXPECT_FLOAT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, max_2x2MinusInfinity_Success)
{
  // Arrange.
  constexpr auto minusInfinity = - std::numeric_limits <double>::infinity ();
  Matrix<double> test_matrix{
    {minusInfinity, minusInfinity},
    {minusInfinity, minusInfinity}
  };
  constexpr double etalon_result {minusInfinity};

  // Act.
  const double test_result = test_matrix.max ();

  // Assert.
  EXPECT_FLOAT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, max_2x2Negative_Success)
{
  // Arrange.
  constexpr auto minusInfinity = - std::numeric_limits <double>::infinity ();
  constexpr auto negativeValue =   std::numeric_limits <double>::min ();
  Matrix<double> test_matrix{
    {negativeValue, minusInfinity},
    {minusInfinity, negativeValue}
  };
  constexpr double etalon_result {negativeValue};

  // Act.
  const double test_result = test_matrix.max ();

  // Assert.
  EXPECT_FLOAT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, max_2x2Zero_Success)
{
  // Arrange.
  constexpr auto minusInfinity = - std::numeric_limits <double>::infinity ();
  constexpr auto negativeValue =   std::numeric_limits <double>::min ();
  Matrix<double> test_matrix{
    {          0.0, minusInfinity},
    {minusInfinity, negativeValue}
  };
  constexpr double etalon_result {0.0};

  // Act.
  const double test_result = test_matrix.max ();

  // Assert.
  EXPECT_FLOAT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, max_2x2Positive_Success)
{
  // Arrange.
  constexpr auto minusInfinity = - std::numeric_limits <double>::infinity ();
  constexpr auto negativeValue =   std::numeric_limits <double>::min ();
  constexpr auto positiveValue =   std::numeric_limits <double>::max ();
  Matrix<double> test_matrix{
    {negativeValue, minusInfinity},
    {positiveValue,           0.0}
  };
  constexpr double etalon_result {positiveValue};

  // Act.
  const double test_result = test_matrix.max ();

  // Assert.
  EXPECT_FLOAT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, max_2x2PlusInfinity_Success)
{
  // Arrange.
  constexpr auto minusInfinity = - std::numeric_limits <double>::infinity ();
  constexpr auto negativeValue =   std::numeric_limits <double>::min ();
  constexpr auto positiveValue =   std::numeric_limits <double>::max ();
  constexpr auto plusInfinity  =   std::numeric_limits <double>::infinity ();
  Matrix<double> test_matrix{
    {minusInfinity, positiveValue},
    {negativeValue, plusInfinity}
  };
  constexpr double etalon_result {plusInfinity};

  // Act.
  const double test_result = test_matrix.max ();

  // Assert.
  EXPECT_FLOAT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, minsize_RowsCountIsMin_Success)
{
  // Arrange.
  Matrix<double> test_matrix (1u, 2u);
  constexpr unsigned int etalon_result {1u};

  // Act.
  const unsigned int test_result = test_matrix.minsize ();

  // Assert.
  EXPECT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, minsize_ColumnsCountIsMin_Success)
{
  // Arrange.
  Matrix<double> test_matrix (2u, 1u);
  constexpr unsigned int etalon_result {1u};

  // Act.
  const unsigned int test_result = test_matrix.minsize ();

  // Assert.
  EXPECT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, minsize_RowsCountAndColumnsCountAreEqual_Success)
{
  // Arrange.
  Matrix<double> test_matrix (3u, 3u);
  constexpr unsigned int etalon_result {3u};

  // Act.
  const unsigned int test_result = test_matrix.minsize ();

  // Assert.
  EXPECT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, columns_Success)
{
  // Arrange.
  Matrix<double> test_matrix{
    {0.0, 0.1, 0.2},
    {1.0, 1.1, 1.2},
    {2.0, 2.1, 2.2}
  };
  constexpr unsigned int etalon_result {3u};

  // Act.
  const unsigned int test_result = test_matrix.columns ();

  // Assert.
  EXPECT_EQ (etalon_result, test_result);
}



TEST_F (MatrixTest, rows_Success)
{
  // Arrange.
  Matrix<double> test_matrix{
    {0.0, 0.1, 0.2},
    {1.0, 1.1, 1.2},
    {2.0, 2.1, 2.2}
  };
  constexpr unsigned int etalon_result {3u};

  // Act.
  const unsigned int test_result = test_matrix.rows ();

  // Assert.
  EXPECT_EQ (etalon_result, test_result);
}
