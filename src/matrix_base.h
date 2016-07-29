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

#if !defined(__MUNKRES_CPP_MATRIX_BASE_H__)
#define __MUNKRES_CPP_MATRIX_BASE_H__



#include <cstdlib>
#include <limits>
#include <cmath>
#include <stdexcept>



namespace munkres
{

template<class T>
class matrix_base
{
    public:
        // Types.
        using elem_t = T;

        // Constants.
        static constexpr elem_t zero = elem_t (0);
        static constexpr elem_t max_val = std::numeric_limits<elem_t>::max ();

        // Interface.
        virtual ~matrix_base () = default;
        virtual const elem_t & operator () (const size_t, const size_t) const noexcept = 0;
        virtual elem_t & operator () (const size_t, const size_t) noexcept = 0;
        virtual size_t columns () const noexcept = 0;
        virtual size_t rows () const noexcept = 0;

        // Default implementation.
        virtual void resize (const size_t rows, const size_t columns, const elem_t = zero)
        {
            if (rows != this->rows () || columns != this->columns () ) {
                throw std::logic_error ("Called function with inappropriate default implementation.");
            }
        }

        virtual elem_t max () const
        {
            elem_t max_elem = rows () && columns () ? operator () (0, 0) : zero;
            for (size_t i = 0; i < rows (); ++i) {
                for (size_t j = 0; j < columns (); ++j) {
                    max_elem = std::max<elem_t>( max_elem, operator () (i, j) );
                }
            }
            return max_elem;
        }

        size_t minsize () const
        {
            return rows () < columns () ? rows () : columns ();
        }

    private:
        // Implementation.
        static constexpr bool is_infinity (const elem_t & elem) noexcept
        {
            return std::isinf (elem);
        }
};

}// namespace munkres

#endif /* !defined(__MUNKRES_CPP_MATRIX_BASE_H__) */
