/*
 *   Copyright (c) 2007 John Weaver
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */



// The most complex example of usage the library.
#include <munkres-cpp/munkres.h>
// The library provides set of adapters for the most popular containers.
// But if you need you can create adapter for any type of container by deriving
// from base matrix class and implement the basic functions which allows navigate
// on container and access to its data.
#include <munkres-cpp/matrix_base.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <cstdlib>

// In general there are several approaches how to implement adapters:
// - use inheritance (inherited from both your container and
//   munkres_cpp::matrix_base);
// - use composition (inherited from munkres_cpp::matrix_base and use your
//   container as member);
template<class T>
class matrix_boost_adapter : public munkres_cpp::matrix_base<T>, boost::numeric::ublas::matrix<T>
{
    public:
        matrix_boost_adapter (const size_t rows, const size_t columns)
            : boost::numeric::ublas::matrix<T>::matrix (rows, columns)
        {
        }

        const T & operator () (const size_t row, const size_t column) const override
        {
            return boost::numeric::ublas::matrix<T>::operator () (row, column);
        };

        T & operator () (const size_t row, const size_t column) override
        {
            return boost::numeric::ublas::matrix<T>::operator () (row, column);
        }

        size_t columns () const override
        {
            return boost::numeric::ublas::matrix<T>::size2 ();
        }

        size_t rows () const override
        {
            return boost::numeric::ublas::matrix<T>::size1 ();
        }

        // If you plan to use the solver with non-square matrices you need reimplement resize
        // function which by default implementation in base class just throw exception.
        void resize (const size_t rows, const size_t columns, const T value = munkres_cpp::matrix_base<T>::zero) override
        {
            if (rows != this->rows () || columns != this->columns () ) {
                const auto rows_old = this->rows ();
                const auto columns_old = this->columns ();
                boost::numeric::ublas::matrix<T>::resize (rows, columns, true);
                if (rows_old < rows) {
                    for (size_t i = rows_old; i < rows; ++i) {
                        for (size_t j = 0; j < columns; ++j) {
                            this->operator() (i, j) = value;
                        }
                    }
                }
                if (columns_old < columns) {
                    for (size_t i = columns_old; i < columns; ++i) {
                        for (size_t j = 0; j < rows; ++j) {
                            this->operator() (j, i) = value;
                        }
                    }
                }

            }
        }
};

int main (int /*argc*/, char * /*argv*/[])
{
    // Set input data (costs matrix) into your adapter.
    matrix_boost_adapter<int> data (2, 3);
    // The library can manage with non-square matrices.
    // In such case the library resize the input matrix and fill
    // new cells by sensible data.
    //           Task I           Task II
    data (0, 0) = 1; data (0, 1) = 2;   // Worker I
    data (0, 0) = 0; data (0, 1) = 9;   // Worker II
    data (0, 0) = 9; data (0, 1) = 9;   // Worker III
    // You are totally responsible for correctness of the input data.
    // Input data must be positive and well defined (no NaN or infinity).

    // If this corresponds logic of your problem domain you can replace
    // positive infinities on maximum value.
    munkres_cpp::replace_infinites (data);

    // The library provide generic function for checking is input data
    // correct and ready for processing.
    if (munkres_cpp::is_data_valid (data) ) {
        // Next you need create the problem solver.
        munkres_cpp::Munkres<int> solver;
        // And apply Munkres algorithm to data.
        solver.solve (data);

        // Now the matrix contains result.
        // Zero value represents selected values.
        // For input above data the result will be:
        // Task I  Task II
        //   1,       0     // Worker I
        //   0,       1     // Worker II
        //   1,       1     // Worker III
        // Which means that sum of the costs 0 and 2 is equal 2 and
        // is minimum cost among the matrix.

        return EXIT_SUCCESS;
    }
    else {
        return EXIT_FAILURE;
    }
}

