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

#if !defined(_MATRIX_TEST_H_)
#define _MATRIX_TEST_H_

#include "matrix.h"
#include <iostream>

template <class T>
bool operator == (const Matrix <T> & a, const Matrix <T> & b)
{
    if (a.rows () != b.rows () || a.columns () != b.columns () ) {
        return false;
    }

    for (unsigned int row = 0; row < a.rows (); ++row) {
        for (unsigned int col = 0; col < a.columns (); ++col) {
            if (a (row, col) != b (row, col) ) {
                return false;
            }
        }
    }

    return true;
}



template <class T>
bool operator != (const Matrix <T> & a, const Matrix <T> & b)
{
    return ! (a == b);
}



template <class T>
std::ostream & operator << (std::ostream & os, const Matrix <T> & m)
{
    const std::string indent ("           ");
    os << "Matrix (" << & m << ") of " << m.rows () << "x" << m.columns () << std::endl;
    for (unsigned int row = 0; row < m.rows (); ++row) {
        os << indent;
        for (unsigned int col = 0; col < m.columns (); ++col) {
            os << std::setw (4) << std::setfill (' ') <<  m (row, col) << " ";
        }
        os << std::endl;
    }

    return os;
}

#endif /* !defined(_MATRIX_TEST_H_) */

