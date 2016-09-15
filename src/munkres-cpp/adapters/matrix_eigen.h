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

#if !defined(_MUNKRES_ADAPTERS_EIGEN_MATRIX_H_)
#define _MUNKRES_ADAPTERS_EIGEN_MATRIX_H_

#include "munkres-cpp/matrix_base.h"
#include <Eigen/Dense>

namespace munkres_cpp
{

template<class T>
class matrix_eigen : public matrix_base<T>, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
{
    public:
        matrix_eigen (const size_t rows, const size_t columns)
            : Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Matrix (rows, columns)
        {
        }

        const T & operator () (const size_t row, const size_t column) const override
        {
            return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::operator () (row, column);
        };

        T & operator () (const size_t row, const size_t column) override
        {
            return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::operator () (row, column);
        }

        size_t columns () const override
        {
            return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::cols ();
        }

        size_t rows () const override
        {
            return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::rows ();
        }

        void resize (const size_t rows, const size_t columns, const T value = matrix_base<T>::zero) override
        {
            if (rows != this->rows () || columns != this->columns () ) {
                const auto rows_old = this->rows ();
                const auto columns_old = this->columns ();
                Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::conservativeResize (rows, columns);
                for (size_t i = rows_old; i < rows; ++i) {
                    for (size_t j = 0; j < columns; ++j) {
                        this->operator() (i, j) = value;
                    }
                }
                for (size_t i = columns_old; i < columns; ++i) {
                    for (size_t j = 0; j < rows; ++j) {
                        this->operator() (j, i) = value;
                    }
                }
            }
        }
};

}// namespace munkres_cpp

#endif /* !defined(_MUNKRES_ADAPTERS_EIGEN_MATRIX_H_) */
