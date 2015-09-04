#include <benchmark/benchmark.h>
//#include <gtest/gtest.h>
#include <vector>

#include "matrixutils.h"
#include "munkres.h"



std::vector <Matrix <double> *> matrices;

constexpr int maxReasonableDataSetCount {100};



static void BM_solve (benchmark::State & state)
{
    state.PauseTiming ();
    if (state.range_x () < matrices.size () ) {
        Munkres munkres;
        while (state.KeepRunning () ) {
            auto matrix = * matrices [state.range_x ()];
            state.ResumeTiming ();
            munkres.solve (matrix);
            state.PauseTiming ();
        }
    }
}
BENCHMARK (BM_solve)->DenseRange (0, maxReasonableDataSetCount);



// Main function.
int main (int argc, char * argv [])
{
    read <double> (matrices);

    benchmark::Initialize (& argc, const_cast <const char **> (argv) );
    benchmark::RunSpecifiedBenchmarks ();
}
