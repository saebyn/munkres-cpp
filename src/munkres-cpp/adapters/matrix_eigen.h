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

namespace munkres
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
            return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::operator () (row, column) ;
        };

        T & operator () (const size_t row, const size_t column) override
        {
            return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::operator () (row, column) ;
        }

        size_t columns () const override
        {
            return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::cols ();
        }

        size_t rows () const override
        {
            return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::rows ();
        }
};

}// namespace munkres

#endif /* !defined(_MUNKRES_ADAPTERS_EIGEN_MATRIX_H_) */
