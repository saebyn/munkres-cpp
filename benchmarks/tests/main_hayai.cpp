#include <hayai.hpp>
#include <vector>

#include "matrixutils.h"
#include "munkres.h"



std::vector <Matrix <double> *> matrices;

size_t i {0};



class MunkresFixture : public ::hayai::Fixture
{
    public:
        void SetUp () override
        {
            matrix = * matrices [i];
        }

        Munkres munkres;
        Matrix <double> matrix;
};



BENCHMARK_F (MunkresFixture, Solve, 5000, 1)
{
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
