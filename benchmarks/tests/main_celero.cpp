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
        virtual std::vector <int64_t> getExperimentValues () const override
        {
            std::vector <int64_t> problemSpace;
            for (int64_t i = 0; i < matrices.size (); ++i) {
                problemSpace.push_back (i);
            }
            return problemSpace;
        }

        void setUp (int64_t experimentValue) override
        {
            matrix = * matrices [experimentValue];
        }

        void tearDown () override
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



// Main function.
int main (int argc, char * argv [])
{
    read <double> (matrices);

    celero::Run (argc, argv);
}
