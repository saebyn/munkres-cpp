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



// Easy way to start with munkres-cpp.
#include "munkres-cpp/munkres.h"
// The library provides set of adapters for the most popular containers
// (for more info explore "adapters" folder).
// If you are lucky then adapter for your container is already implemented.
#include "munkres-cpp/adapters/matrix_boost.h"
#include <cstdlib>

int main (int /*argc*/, char * /*argv*/[])
{
    // In such case you just need just create matrix of corresponding type,
    // set input data (const) and pass it to the solver.

    // Set input data (costs matrix).
    munkres_cpp::matrix_boost<double> data (2, 2);
    data (0, 0) = 1.0; data (0, 1) = 3.0;
    data (0, 0) = 5.0; data (0, 1) = 9.0;
    // Don't forget! you are responsible for correctness of the input data.

    // Create the solver and apply the algorithm to data.
    munkres_cpp::Munkres<double> solver;
    solver.solve (data);

    // Now the matrix contains result.

    return EXIT_SUCCESS;
}

