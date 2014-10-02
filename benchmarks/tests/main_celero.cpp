#include <celero/Celero.h>
#include <vector>

#include "matrixutils.h"
#include "munkres.h"



std::vector <Matrix <double> *> matrices;



class MunkresFixture : public celero::TestFixture
{
    public:
        MunkresFixture  () = default;
        ~MunkresFixture () = default;
        virtual std::vector <int64_t> getExperimentValues () const
        {
            std::vector <int64_t> problemSpace;
            for (int64_t i = 0; i < matrices.size (); ++i) {
                problemSpace.push_back (i);
            }
            return problemSpace;
        }

        virtual void setUp (int64_t experimentValue)
        {
            matrix = * matrices [experimentValue];
        }

        virtual void tearDown ()
        {
        }

        Matrix <double> matrix;
};



BASELINE_F (Munkres, Solve, MunkresFixture, 10, 500)
{
    Munkres munkres;
    auto m = this->matrix;
    munkres.solve (m);
}



BENCHMARK_F (Munkres, Solve, MunkresFixture, 10, 500)
{
    Munkres munkres;
    auto m = this->matrix;
    munkres.solve (m);
}



BASELINE (Muknres, Solve, 5, 10)
{
    Munkres munkres;
    auto matrix = * matrices [0];
    munkres.solve (matrix);
}



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

    celero::Run (argc, argv);
}
