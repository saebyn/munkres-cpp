#if !defined(_MATRIX_UTILS_H_)
#define _MATRIX_UTILS_H_

#include "matrix.h"
#include <fstream>
#include <random>
#include <limits>
#include <iostream>
#include <iomanip>



const std::string fileName = "matrices.txt";



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



template <class T>
std::istream & operator >> (std::istream & is, Matrix <T> & m)
{
    std::string marker;
    is >> marker;
    if ("Matrix" == marker) {
        std::string unused;
        std::string size;
        is >> unused;
        is >> unused;
        is >> size;
        const size_t delimiter = size.find ("x");
        if (std::string::npos != delimiter) {
            const size_t rows    = stoi (size.substr (0, delimiter) );
            const size_t columns = stoi (size.substr (delimiter + 1) );
            if (rows && columns) {
                m.resize (rows, columns);
                for (size_t row = 0; row < rows; ++row) {
                    for (size_t col = 0; col < columns; ++col) {
                        is >>  m (row, col);
                    }
                }
            }
        }
    }

    return is;
}



template <typename T>
bool write (const std::vector <Matrix <T> *> & matrices)
{
    std::fstream os;
    os.open (fileName, std::fstream::out/* | std::fstream::binary*/);

    for (size_t i = 0; i < matrices.size (); ++i) {
        os << * matrices [i];
    }
    os.close ();

    return true;
}



template <typename T>
bool read (std::vector <Matrix <T> *> & matrices)
{
    std::fstream is;
    is.open (fileName, std::fstream::in/* | std::fstream::binary*/);

    Matrix <T> * matrix = new Matrix <T>;
    while (is >> * matrix) {
        matrices.push_back (matrix);
        matrix = new Matrix <T>;
    }
    delete matrix;
    is.close ();

    return true;
}



template <typename T>
Matrix<double> generate_random_matrix (const size_t nrows, const size_t ncols)
{
    Matrix<T> matrix(nrows, ncols);

    // Prepare random generator.
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution (0.0, std::numeric_limits<double>::max () );

    // Initialize matrix with random values.
    for ( size_t row = 0 ; row < matrix.rows() ; row++ ) {
        for ( size_t col = 0 ; col < matrix.columns() ; col++ ) {
            matrix(row,col) = distribution (generator);
        }
    }

    return matrix;
}

#endif /* !defined(_MATRIX_UTILS_H_) */
