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

#include "matrix.h"
#include <vector>


// Set of functions for two-dimensional std::vector.
template<typename T>
Matrix<T> convert_std_2d_vector_to_munkres_matrix (const std::vector<std::vector<T>> & vector);

template<typename T>
void fill_std_2d_vector_from_munkres_matrix (std::vector<std::vector<T>> & vector, const Matrix<T> & matrix);

void solve (std::vector<std::vector<double>> & m);

#ifndef USE_EXPORT_KEYWORD
#include "std_2d_vector.cpp"
//#define export /*export*/
#endif

#endif /* !defined(_MUNKRES_ADAPTERS_STD_2D_VECTOR_H_) */
