#include <benchmark/benchmark.h>
#include <vector>

#include "matrixutils.h"
#include "munkres-cpp/munkres.h"



std::vector<munkres_cpp::Matrix<double> *> matrices;

constexpr int maxReasonableDataSetCount {100};



static void BM_solve (benchmark::State & state)
{
    state.PauseTiming ();
    if (state.range_x () < (matrices.size () > 0u ? static_cast<ssize_t>(matrices.size () ) : 0) ) {
        munkres_cpp::Munkres<double> munkres;
        while (state.KeepRunning () ) {
            auto matrix = *matrices [state.range_x ()];
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
    read<double>(matrices);

    benchmark::Initialize ( &argc, argv);
    benchmark::RunSpecifiedBenchmarks ();
}
