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

#include "raw_2d_array.h"
#include "munkres.h"

template <typename T, const unsigned int dimention1, const unsigned int dimention2>
Matrix <T> convert_raw_2d_array_to_munkres_matrix (const T array [dimention1][dimention2])
{
  Matrix <T> matrix (dimention1, dimention2);
  for (int i = 0; i < dimention1; ++i) {
    for (int j = 0; j < dimention2; ++j) {
      matrix (i, j) = array [i][j];
    }
  }

  return matrix;
};

template <typename T, const unsigned int dimention1, const unsigned int dimention2>
void fill_raw_2d_array_from_munkres_matrix (T array [dimention1][dimention2], const Matrix <T> & matrix)
{
  for (int i = 0; i < dimention1; ++i) {
    for (int j = 0; j < dimention2; ++j) {
      array [i][j] = matrix (i, j);
    }
  }
};

template <const unsigned int dimention1, const unsigned int dimention2>
void solve(double m [dimention1][dimention2])
{
  auto matrix = convert_raw_2d_array_to_munkres_matrix<double, dimention1, dimention2>(m);
  Munkres munkres;
  munkres.solve (matrix);
  fill_raw_2d_array_from_munkres_matrix<double, dimention1, dimention2>(m, matrix);
};
