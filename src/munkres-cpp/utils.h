#if !defined(__MUNKRES_CPP_UTILS_H__)
#define __MUNKRES_CPP_UTILS_H__

#include <cmath>
#include <cassert>
#include "munkres-cpp/matrix_base.h"



namespace munkres_cpp
{

template<typename T>
void replace_infinites (matrix_base<T> & matrix)
{
    if (!std::numeric_limits<T>::has_infinity) {
        return;
    }

    const size_t rows = matrix.rows (),
                 columns = matrix.columns ();

    if (!rows || !columns) {
        return;
    }

    T max = matrix (0, 0);
    constexpr auto infinity = std::numeric_limits<T>::infinity ();

    // Find the greatest value in the matrix that isn't infinity.
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < columns; col++) {
            if (matrix (row, col) != infinity) {
                if (max == infinity) {
                    max = matrix (row, col);
                } else {
                    max = std::max<T>( max, matrix (row, col) );
                }
            }
        }
    }

    // A value higher than the maximum value present in the matrix.
    if (max == infinity) {
        // This case only occurs when all values are infinite.
        max = 0;
    } else {
        max++;
    }

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < columns; col++) {
            if (matrix (row, col) == infinity) {
                matrix (row, col) = max;
            }
        }
    }
}



template<typename T>
bool is_data_valid (matrix_base<T> & matrix)
{
    // Check if present negative values?
    if (std::numeric_limits<T>::is_signed) {
        for (size_t i = 0; i < matrix.rows (); ++i) {
            for (size_t j = 0; j < matrix.columns (); ++j) {
                if (matrix (i, j) < T (0) ) {
                    return false;
                }
            }
        }
    }

    // Check if present non normal (NaN, inf, etc.) values?
    if (!std::numeric_limits<T>::is_integer) {
        for (size_t i = 0; i < matrix.rows (); ++i) {
            for (size_t j = 0; j < matrix.columns (); ++j) {
                const auto x = std::fpclassify (matrix (i, j) );
                if (x != FP_ZERO && x != FP_NORMAL) {
                    return false;
                }
            }
        }
    }

    return true;
}

}// namespace munkres_cpp

#endif /* !defined(__MUNKRES_CPP_UTILS_H__) */
