#include "math/gauss.h"

#include <cmath>
#include <cstdlib>

namespace math {

bool gauss(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double>* x)
{
    int H = A.size();

    for (int i = 0; i < H; ++i) {
        // --- choose pivot.
        int pivot = i;
        for (int j = i + 1; j < H; ++j) {
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
            for (int j = i; j < A[i].size(); ++j) {
                A[i][j] /= v;
            }
            b[i] /= v;
        }

        // --- subtract
        for (int j = 0; j < H; ++j) {
            if (i == j)
                continue;
            double v = A[j][i];
            for (int k = i; k < A[j].size(); ++k) {
                A[j][k] -= A[i][k] * v;
            }
            b[j] -= b[i] * v;
        }
    }

    *x = b;
    return true;
}

} // namespace math
