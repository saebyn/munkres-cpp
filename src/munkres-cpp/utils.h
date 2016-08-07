#if !defined(__MUNKRES_CPP_UTILS_H__)
#define __MUNKRES_CPP_UTILS_H__

#include <cmath>
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



// Macro for trivial support of Design By Contract.
#define DBC_MODE_NONE       0
#define DBC_MODE_MESSAGE    1
#define DBC_MODE_ASSERT     2

#ifndef DEBUG_WITH_DBC
#define DEBUG_WITH_DBC DBC_MODE_NONE
#endif//DEBUG_WITH_DBC

#ifdef  DEBUG_WITH_DBC

#ifdef  STRINGIFICATION
#error  STRINGIFICATION macro already defined!
#endif//STRINGIFICATION
#define STRINGIFICATION(x) #x

#if DEBUG_WITH_DBC == DBC_MODE_ASSERT
    #define REQUIRE(CONDITION, MESSAGE) \
    do { \
        if (!(CONDITION) ) { \
            throw std::runtime_error ( \
                      "Precondition error: " \
                      + std::string (STRINGIFICATION (CONDITION) ) + " at " \
                      + std::string (__FILE__) + ":" + std::to_string (__LINE__) + ". " \
                      + std::string (MESSAGE) ); \
        } \
    } while (0);

    #define ENSURE(CONDITION, MESSAGE) \
    do { \
        if (!(CONDITION) ) { \
            throw std::runtime_error ( \
                      "Postcondition error: " \
                      + std::string (STRINGIFICATION (CONDITION) ) + " at " \
                      + std::string (__FILE__) + ":" + std::to_string (__LINE__) + ". " \
                      + std::string (MESSAGE) ); \
        } \
    } while (0);

    #define INVARIANT(CONDITION, MESSAGE) \
    do { \
        if (!(CONDITION) ) { \
            throw std::runtime_error ( \
                      "Invariant error: " \
                      + std::string (STRINGIFICATION (CONDITION) ) + " at " \
                      + std::string (__FILE__) + ":" + std::to_string (__LINE__) + ". " \
                      + std::string (MESSAGE) ); \
        } \
    } while (0);

#elif DEBUG_WITH_DBC == DBC_MODE_MESSAGE
    #define STRINGIFICATION(x) #x
    #define REQUIRE(CONDITION, MESSAGE) \
    do { \
        if (!(CONDITION) ) { \
            std::cout \
                << "Precondition error: " \
                << std::string (STRINGIFICATION (CONDITION) ) + " at " \
                << std::string (__FILE__) << ":" << std::to_string (__LINE__) << ". " \
                << std::string (MESSAGE) \
                << std::endl; \
        } \
    } while (0);

    #define ENSURE(CONDITION, MESSAGE) \
    do { \
        if (!(CONDITION) ) { \
            std::cout \
                << "Postcondition error: " \
                << std::string (STRINGIFICATION (CONDITION) ) + " at " \
                << std::string (__FILE__) << ":" << std::to_string (__LINE__) << ". " \
                << std::string (MESSAGE) \
                << std::endl; \
        } \
    } while (0);

    #define INVARIANT(CONDITION, MESSAGE) \
    do { \
        if (!(CONDITION) ) { \
            std::cout \
                << "Invariant error: " \
                << std::string (STRINGIFICATION (CONDITION) ) + " at " \
                << std::string (__FILE__) << ":" << std::to_string (__LINE__) << ". " \
                << std::string (MESSAGE) \
                << std::endl; \
        } \
    } while (0);

#else //DEBUG_WITH_DBC || DEBUG_WITH_DBC_ASSERT
    #define REQUIRE(CONDITION, MESSAGE);
    #define ENSURE(CONDITION, MESSAGE);
    #define INVARIANT(CONDITION, MESSAGE);
#endif//DEBUG_WITH_DBC || DEBUG_WITH_DBC_ASSERT

#endif//DEBUG_WITH_DBC

}// namespace munkres_cpp

#endif /* !defined(__MUNKRES_CPP_UTILS_H__) */
