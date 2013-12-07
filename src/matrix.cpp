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

#include "matrix.h"

#include <cassert>
#include <cstdlib>
#include <algorithm>

/*export*/ template <class T>
Matrix<T>::Matrix() {
  m_rows = 0;
  m_columns = 0;
  m_matrix = NULL;
}


/*export*/ template <class T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init) {
  m_matrix = NULL;
  m_rows = init.size();
  if ( m_rows == 0 ) {
    m_columns = 0;
  } else {
    m_columns = init.begin()->size();
    if ( m_columns > 0 ) {
      resize(m_rows, m_columns);
    }
  }

  int i = 0, j;
  for ( auto row = init.begin() ; row != init.end() ; ++row, ++i ) {
    assert ( row->size() == m_columns && "All rows must have the same number of columns." );
    j = 0;
    for ( auto value = row->begin() ; value != row->end() ; ++value, ++j ) {
      m_matrix[i][j] = *value;
    }
  }
}

/*export*/ template <class T>
Matrix<T>::Matrix(const Matrix<T> &other) {
  if ( other.m_matrix != NULL ) {
    // copy arrays
    m_matrix = NULL;
    resize(other.m_rows, other.m_columns);
    for ( unsigned int i = 0 ; i < m_rows ; i++ ) {
      for ( unsigned int j = 0 ; j < m_columns ; j++ ) {
        m_matrix[i][j] = other.m_matrix[i][j];
      }
    }
  } else {
    m_matrix = NULL;
    m_rows = 0;
    m_columns = 0;
  }
}

/*export*/ template <class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns) {
  m_matrix = NULL;
  resize(rows, columns);
}

/*export*/ template <class T>
Matrix<T> &
Matrix<T>::operator= (const Matrix<T> &other) {
  if ( other.m_matrix != NULL ) {
    // copy arrays
    resize(other.m_rows, other.m_columns);
    for ( unsigned int i = 0 ; i < m_rows ; i++ ) {
      for ( unsigned int j = 0 ; j < m_columns ; j++ ) {
          m_matrix[i][j] = other.m_matrix[i][j];
      }
    }
  } else {
    // free arrays
    for ( unsigned int i = 0 ; i < m_columns ; i++ ) {
      delete [] m_matrix[i];
    }

    delete [] m_matrix;

    m_matrix = NULL;
    m_rows = 0;
    m_columns = 0;
  }
  
  return *this;
}

/*export*/ template <class T>
Matrix<T>::~Matrix() {
  if ( m_matrix != NULL ) {
    // free arrays
    for ( unsigned int i = 0 ; i < m_rows ; i++ ) {
      delete [] m_matrix[i];
    }

    delete [] m_matrix;
  }
  m_matrix = NULL;
}

/*export*/ template <class T>
void
Matrix<T>::resize(unsigned int rows, unsigned int columns, T default_value) {
  assert ( rows > 0 && columns > 0 && "Columns and rows must exist." );

  if ( m_matrix == NULL ) {
    // alloc arrays
    m_matrix = new T*[rows]; // rows
    for ( unsigned int i = 0 ; i < rows ; i++ ) {
      m_matrix[i] = new T[columns]; // columns
    }

    m_rows = rows;
    m_columns = columns;
    clear();
  } else {
    // save array pointer
    T **new_matrix;
    // alloc new arrays
    new_matrix = new T*[rows]; // rows
    for ( unsigned int i = 0 ; i < rows ; i++ ) {
      new_matrix[i] = new T[columns]; // columns
      for ( unsigned int j = 0 ; j < columns ; j++ ) {
        new_matrix[i][j] = default_value;
      }
    }

    // copy data from saved pointer to new arrays
    unsigned int minrows = std::min<unsigned int>(rows, m_rows);
    unsigned int mincols = std::min<unsigned int>(columns, m_columns);
    for ( unsigned int x = 0 ; x < minrows ; x++ ) {
      for ( unsigned int y = 0 ; y < mincols ; y++ ) {
        new_matrix[x][y] = m_matrix[x][y];
      }
    }

    // delete old arrays
    if ( m_matrix != NULL ) {
      for ( unsigned int i = 0 ; i < m_rows ; i++ ) {
        delete [] m_matrix[i];
      }

      delete [] m_matrix;
    }

    m_matrix = new_matrix;
  }

  m_rows = rows;
  m_columns = columns;
}

/*export*/ template <class T>
void
Matrix<T>::clear() {
  assert( m_matrix != NULL );

  for ( unsigned int i = 0 ; i < m_rows ; i++ ) {
    for ( unsigned int j = 0 ; j < m_columns ; j++ ) {
      m_matrix[i][j] = 0;
    }
  }
}

/*export*/ template <class T>
inline T&
Matrix<T>::operator ()(unsigned int x, unsigned int y) {
  assert ( x < m_rows );
  assert ( y < m_columns );
  assert ( m_matrix != NULL );
  return m_matrix[x][y];
}


/*export*/ template <class T>
inline const T&
Matrix<T>::operator ()(unsigned int x, unsigned int y) const {
  assert ( x < m_rows );
  assert ( y < m_columns );
  assert ( m_matrix != NULL );
  return m_matrix[x][y];
}


/*export*/ template <class T>
const T
Matrix<T>::min() const {
  assert( m_matrix != NULL );
  assert ( m_rows > 0 );
  assert ( m_columns > 0 );
  T min = m_matrix[0][0];

  for ( unsigned int i = 0 ; i < m_rows ; i++ ) {
    for ( unsigned int j = 0 ; j < m_columns ; j++ ) {
      min = std::min<T>(min, m_matrix[i][j]);
    }
  }

  return min;
}


/*export*/ template <class T>
const T
Matrix<T>::max() const {
  assert( m_matrix != NULL );
  assert ( m_rows > 0 );
  assert ( m_columns > 0 );
  T max = m_matrix[0][0];

  for ( unsigned int i = 0 ; i < m_rows ; i++ ) {
    for ( unsigned int j = 0 ; j < m_columns ; j++ ) {
      max = std::max<T>(max, m_matrix[i][j]);
    }
  }

  return max;
}
