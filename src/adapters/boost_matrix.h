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

#if !defined(_MUNKRES_ADAPTERS_BOOST_MATRIX_H_)
#define _MUNKRES_ADAPTERS_BOOST_MATRIX_H_

#include "matrix.h"
#include <boost/numeric/ublas/matrix.hpp>


// Set of functions for boost matrix.
template <typename T>
Matrix <T> convert_boost_matrix_to_munkres_matrix (const boost::numeric::ublas::matrix <T> &);

template <typename T>
void fill_boost_matrix_from_munkres_matrix (boost::numeric::ublas::matrix <T> & boost_matrix, const Matrix <T> &);

void solve(boost::numeric::ublas::matrix <double> &);

#ifndef USE_EXPORT_KEYWORD
#include "boost_matrix.cpp"
//#define export /*export*/
#endif

#endif /* !defined(_MUNKRES_ADAPTERS_BOOST_MATRIX_H_) */
