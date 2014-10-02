#include <hayai.hpp>
//#include <gtest/gtest.h>
#include <vector>

#include "matrixutils.h"
#include "munkres.h"



std::vector <Matrix <double> *> matrices;



BENCHMARK (Muknres, Solve, 5, 10)
{
    Munkres munkres;
    auto matrix = * matrices [0];
    munkres.solve (matrix);
}



// Main function.
int main (int argc, char * argv [])
{
    read <double> (matrices);

    hayai::ConsoleOutputter consoleOutputter;
    hayai::Benchmarker::AddOutputter (consoleOutputter);
    hayai::Benchmarker::RunAllTests ();
}
