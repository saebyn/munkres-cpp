#include <hayai.hpp>
//#include <gtest/gtest.h>
#include <vector>

#include "matrixutils.h"
#include "munkres.h"



std::vector <Matrix <double> *> matrices;

size_t i {0};



BENCHMARK (Munkres, Solve, 5, 1000)
{
    Munkres munkres;
    auto matrix = * matrices [i];
    munkres.solve (matrix);
}



// Main function.
int main (int argc, char * argv [])
{
    read <double> (matrices);

    hayai::ConsoleOutputter consoleOutputter;
    hayai::Benchmarker::AddOutputter (consoleOutputter);
    for (const auto x : matrices) {
        hayai::Benchmarker::RunAllTests ();
        ++i;
    }
}
