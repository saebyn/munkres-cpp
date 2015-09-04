#include <vector>

#include "matrixutils.h"
#include "munkres.h"



// Main function.
int main (int argc, char * argv [])
{
    std::vector <Matrix <double> *> matrices;
    read <double> (matrices);


    for (size_t i = 0; i < matrices.size (); ++i) {
        std::cout << "Test case " << i + 1 << " from " << matrices.size () << std::endl;
        Munkres munkres;
        auto matrix = * matrices [i];
        munkres.solve (matrix);
    }
}
