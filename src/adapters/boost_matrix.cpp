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

#include "boost_matrix.h"
#include "munkres.h"

template <typename T>
Matrix <T> convert_boost_matrix_to_munkres_matrix (const boost::numeric::ublas::matrix <T> & boost_matrix)
{
  const auto dimention = std::min (boost_matrix.size1 (), boost_matrix.size2 () );
  Matrix <T> matrix (dimention, dimention);
  for (int i = 0; i < dimention; ++i) {
    for (int j = 0; j < dimention; ++j) {
      matrix (i, j) = boost_matrix (i, j);
    }
  }

  return matrix;
};

template <typename T>
void fill_boost_matrix_from_munkres_matrix (boost::numeric::ublas::matrix <T> & boost_matrix, const Matrix <T> & matrix)
{
  const auto dimention = std::min (boost_matrix.size1 (), boost_matrix.size2 () );
  for (int i = 0; i < dimention; ++i) {
    for (int j = 0; j < dimention; ++j) {
      boost_matrix (i, j) = matrix (i, j);
    }
  }
};

void solve(boost::numeric::ublas::matrix <double> & boost_matrix)
{
  auto matrix = convert_boost_matrix_to_munkres_matrix<double>(boost_matrix);
  Munkres munkres;
  munkres.solve (matrix);
  fill_boost_matrix_from_munkres_matrix<double>(boost_matrix, matrix);
};
