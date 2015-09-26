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

#ifndef RAW2DARRAY_H
#define RAW2DARRAY_H

#include "adapter.h"

template<typename Data> class Std2dVectorAdapter : public Adapter<Data,std::vector<std::vector <Data>>>
{
public:
    virtual Matrix<Data> convertToMatrix(const std::vector<std::vector <Data>> &vector) const override
    {
        const int rows = vector.size();
        const int cols = vector[0].size();
        Matrix <Data> matrix (rows, cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                matrix(i, j) = vector[i][j];
            }
        }
        return matrix;
    }

    virtual void convertFromMatrix(std::vector<std::vector <Data>> &vector,const Matrix<Data> &matrix) const override
    {
        vector.clear();

        const int rows = matrix.rows();
        const int cols = matrix.columns();
        for (int i = 0; i < rows; ++i)
        {
            std::vector <Data> temp;
            for (int j = 0; j < cols; ++j)
            {
                temp.push_back(matrix(i,j));
            }

            vector.push_back(temp);
        }
    }
};

#endif // RAW2DARRAY_H
