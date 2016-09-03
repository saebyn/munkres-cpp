#include <gtest/gtest.h>
#include "munkres-cpp/utils.h"
#include "matrix_test.h"



template <typename T>
class UtilsTestSigned : public ::testing::Test
{
};

typedef ::testing::Types <
    signed                  char
  , signed      short       int
  , signed                  int
  , signed      long        int
  , signed      long long   int
  , float
  , double
  , long double> TypesSigned;

TYPED_TEST_CASE (UtilsTestSigned, TypesSigned);



template <typename T>
class UtilsTestFloating : public ::testing::Test
{
};

typedef ::testing::Types <
    float
  , double
  , long double> TypesFloating;

TYPED_TEST_CASE (UtilsTestFloating, TypesFloating);



TYPED_TEST (UtilsTestFloating, replace_infinites_4x4Case001_Success)
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



TYPED_TEST (UtilsTestFloating, replace_infinites_4x4Case002_Success)
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



TYPED_TEST (UtilsTestFloating, replace_infinites_4x4Case003_Success)
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



TYPED_TEST (UtilsTestFloating, replace_infinites_4x4Case004_Success)
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



TYPED_TEST (UtilsTestFloating, replace_infinites_4x4Case005_Success)
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



TYPED_TEST (UtilsTestSigned, is_data_valid_Success)
{
    // Arrange.
    Matrix<TypeParam> test_matrix {
        { 1.0,      0.0},
        { 3.0,      2.0},
    };

    // Act, Assert.
    EXPECT_TRUE (munkres_cpp::is_data_valid (test_matrix) );
}



TYPED_TEST (UtilsTestSigned, is_data_valid_negative_Failed)
{
    // Arrange.
    Matrix<TypeParam> test_matrix {
        { 1.0,      0.0},
        { 3.0,     -2.0},
    };

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (test_matrix) );
}



TYPED_TEST (UtilsTestFloating, is_data_valid_infinity_Failed)
{
    // Arrange.
    Matrix<TypeParam> test_matrix {
        { 1.0,      0.0},
        { 3.0,      std::numeric_limits<TypeParam>::infinity ()},
    };

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (test_matrix) );
}



TYPED_TEST (UtilsTestFloating, is_data_valid_minus_infinity_Failed)
{
    // Arrange.
    Matrix<TypeParam> test_matrix {
        { 1.0,      0.0},
        { 3.0,    - std::numeric_limits<TypeParam>::infinity ()},
    };

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (test_matrix) );
}



TYPED_TEST (UtilsTestFloating, is_data_valid_NaN_Failed)
{
    // Arrange.
    Matrix<TypeParam> test_matrix {
        { 1.0,      0.0},
        { 3.0,      std::numeric_limits<TypeParam>::quiet_NaN ()},
    };

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (test_matrix) );
}



TYPED_TEST (UtilsTestFloating, is_data_valid_denormalized_Failed)
{
    // Arrange.
    Matrix<TypeParam> test_matrix {
        { 1.0,      0.0},
        { 3.0,      std::numeric_limits<TypeParam>::min () / TypeParam (2.0)},
    };

    // Act, Assert.
    EXPECT_FALSE (munkres_cpp::is_data_valid (test_matrix) );
}

