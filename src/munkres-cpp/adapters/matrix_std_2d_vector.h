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

#if !defined(_MUNKRES_ADAPTERS_STD_2D_VECTOR_H_)
#define _MUNKRES_ADAPTERS_STD_2D_VECTOR_H_

#include "munkres-cpp/munkres.h"
#include <vector>

namespace munkres_cpp
{

template<class T>
class matrix_std_2d_vector : public matrix_base<T>
{
    public:
        matrix_std_2d_vector (std::vector<std::vector<T>> & data)
            : data {data}
        {
        }

        const T & operator () (const size_t row, const size_t column) const override
        {
            return data [row][column];
        };

        T & operator () (const size_t row, const size_t column) override
        {
            return data [row][column];
        }

        size_t columns () const override
        {
            size_t columns = data.size () ? data [0].size () : 0;
            for (size_t i = 0; i < data.size (); ++i) {
                columns = std::min (columns, data [i].size () );
            }
            return columns;
        }

        size_t rows () const override
        {
            return data.size ();
        }

        void resize (const size_t rows, const size_t columns, const T value = matrix_base<T>::zero) override
        {
            if (rows != this->rows () ) {
                data.resize (rows);
                if (columns != this->columns () ) {
                    for (size_t i = 0; i < rows; ++i) {
                        data [i].resize (columns, value);
                    }
                }
            }
        }

    private:
        std::vector<std::vector<T>> & data;
};

}// namespace munkres_cpp

#endif /* !defined(_MUNKRES_ADAPTERS_STD_2D_VECTOR_H_) */
