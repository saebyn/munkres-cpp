//#include <gtest/gtest.h>
#include <vector>
#include <limits>
#include <string>

#include "matrixutils.h"
#include "munkres.h"



// Main function.
int main (int argc, char * argv [])
{
    std::vector <Matrix <double> *> matrices;
    read <double> (matrices);


    size_t iterations  = 1000;
    size_t runs        = 10;
    if (3 == argc) {
        runs        = std::stoi (argv [1]);
        iterations  = std::stoi (argv [2]);
    }
    std::cout << "Prepare to launch " << runs << " runs with " << iterations << " iterations each." << std::endl;

    for (size_t i = 0; i < matrices.size (); ++i) {
        std::cout << "Test case " << i + 1 << " from " << matrices.size () << std::endl;
        uint64_t rdtscMin = std::numeric_limits <uint64_t>::max ();
        for (size_t j = 0; j < runs; ++j) {
            uint64_t rdtscMinRun = std::numeric_limits <uint64_t>::max ();
            for (size_t k = 0; k < iterations; ++k) {
                Munkres munkres;
                auto matrix = * matrices [i];
                uint64_t rdtsc = __rdtsc ();
                munkres.solve (matrix);
                rdtsc = __rdtsc () - rdtsc;
                rdtscMinRun = std::min (rdtscMinRun, rdtsc);
            }
            std::cout << "Run " << std::setw (4) << j << ": " << rdtscMinRun << std::endl;
            rdtscMin = std::min (rdtscMin, rdtscMinRun);
        }
        std::cout << "The best: " << rdtscMin << std::endl;
    }
}
