#include "math/gauss.h"

#include <cmath>
#include <cstdlib>

namespace math {

bool gauss(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double>* x)
{
    size_t H = A.size();

    for (size_t i = 0; i < H; ++i) {
        // --- choose pivot.
        size_t pivot = i;
        for (size_t j = i + 1; j < H; ++j) {
            if (abs(A[pivot][i]) < abs(A[j][i]))
                pivot = j;
        }
        if (A[pivot][i] == 0)
            return false;
        std::swap(A[pivot], A[i]);
        std::swap(b[pivot], b[i]);

        // --- divide each row by A[i][i].
        {
            double v = A[i][i];
            for (size_t j = i; j < A[i].size(); ++j) {
                A[i][j] /= v;
            }
            b[i] /= v;
        }

        // --- subtract
        for (size_t j = 0; j < H; ++j) {
            if (i == j)
                continue;
            double v = A[j][i];
            for (size_t k = i; k < A[j].size(); ++k) {
                A[j][k] -= A[i][k] * v;
            }
            b[j] -= b[i] * v;
        }
    }

    *x = b;
    return true;
}

} // namespace math
