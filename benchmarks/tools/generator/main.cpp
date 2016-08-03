#include <cstdlib>
#include "matrixutils.h"
#include <string>



int main (int argc, char * argv [])
{
    std::vector<munkres_cpp::Matrix<double> *> matrices;

    for (int i = 1; i < argc; ++i) {
        const size_t size = std::stoi (argv [i]);
        munkres_cpp::Matrix<double> * matrix = new munkres_cpp::Matrix<double>;
        *matrix = generate_random_matrix<double>(size, size);
        matrices.push_back (matrix);
    }
    write<double>(matrices);

    return EXIT_SUCCESS;
}
