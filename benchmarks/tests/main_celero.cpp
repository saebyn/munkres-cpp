#include <celero/Celero.h>
#include <vector>

#include "matrixutils.h"
#include "munkres.h"



std::vector <Matrix <double> *> matrices;

size_t i {0};



class MunkresFixture : public celero::TestFixture
{
    public:
        void setUp (int64_t) override
        {
            matrix = * matrices [i];
        }

        Munkres munkres;
        Matrix <double> matrix;
};



BASELINE_F (Munkres, Solve, MunkresFixture, 5000, 1)
{
    munkres.solve (matrix);
}



BENCHMARK_F (Munkres, Solve, MunkresFixture, 5000, 1)
{
    munkres.solve (matrix);
}



// Main function.
int main (int argc, char * argv [])
{
    read <double> (matrices);

    for (const auto x : matrices) {
        celero::Run (argc, argv);
        ++i;
    }
}
