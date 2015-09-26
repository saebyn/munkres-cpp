/*
 *   Copyright (c) 2015 Miroslav Krajicek
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

#ifndef STD2DARRAYADAPTER_H
#define STD2DARRAYADAPTER_H

#include "adapter.h"

template<typename Data, size_t rows, size_t columns> class Std2dArrayAdapter : public Adapter<Data, std::array <std::array <Data, columns>, rows>>
{
public:
    virtual Matrix<Data> convertToMatrix(const std::array <std::array <Data, columns>, rows>  &array) const override
    {
        Matrix <Data> matrix(rows, columns);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                matrix (i, j) = array [i][j];
            }
        }
        return matrix;
    }

    virtual void convertFromMatrix(std::array <std::array <Data, columns>, rows> &array,const Matrix<Data> &matrix) const override
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                array [i][j] = matrix (i, j);
            }
        }
    }
};

#endif // STD2DARRAYADAPTER_H
