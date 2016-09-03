#include "munkres-cpp/munkres.h"
#include <cstdlib>



int main ()
{
    {
        munkres_cpp::Matrix<double> data {
            {1.0, 2.0}
          , {3.0, 1.0}
        };
        munkres_cpp::Munkres<double> solver;
        munkres_cpp::replace_infinites (data);
        if (munkres_cpp::is_data_valid (data) ) {
            solver.solve (data);
        }
    }

    {
        munkres_cpp::Matrix<int> data {
            {1,   2}
          , {3,   1}
        };
        munkres_cpp::Munkres<int> solver;
        if (munkres_cpp::is_data_valid (data) ) {
            solver.solve (data);
        }
    }


    return EXIT_SUCCESS;
}
