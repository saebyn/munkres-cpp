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

#include "std_2d_vector.h"
#include "munkres.h"

template<typename T>
Matrix<T> convert_std_2d_vector_to_munkres_matrix (const std::vector<std::vector<T>> & vector)
{
    const int dimention = vector.size ();
    Matrix<T> matrix (dimention, dimention);
    for (int i = 0; i < dimention; ++i) {
        for (int j = 0; j < dimention; ++j) {
            matrix (i, j) = vector [i][j];
        }
    }

    return matrix;
};

template<typename T>
void fill_std_2d_vector_from_munkres_matrix (std::vector<std::vector<T>> & vector, const Matrix<T> & matrix)
{
    const int dimention = vector.size ();
    for (int i = 0; i < dimention; ++i) {
        for (int j = 0; j < dimention; ++j) {
            vector [i][j] = matrix (i, j);
        }
    }
};

void solve (std::vector<std::vector<double>> & m)
{
    auto matrix = convert_std_2d_vector_to_munkres_matrix<double>(m);
    Munkres munkres;
    munkres.solve (matrix);
    fill_std_2d_vector_from_munkres_matrix<double>(m, matrix);
};
