#include "math/knapsack.h"

namespace math {

// v[k][w] is the largest value with
//   - 0-|k| items are used
//   - wegiht is less than or equal to |w|.
//
// Then, v[k][w] = max(v[k][w - 1], v[k - 1][w - ws[k]] + vs[k])
int knapsack(int W, int N, const std::vector<int>& ws, const std::vector<int>& vs)
{
    std::vector<std::vector<int> > v(N, std::vector<int>(W + 1));

    for (int w = ws[0]; w <= W; ++w) {
        v[0][w] = vs[0];
    }
    for (int k = 1; k < N; ++k) {
        for (int w = 1; w <= W; ++w) {
            v[k][w] = std::max(v[k][w-1], v[k-1][w]);
            if (w - ws[k] >= 0) {
                v[k][w] = std::max(v[k][w], v[k-1][w-ws[k]] + vs[k]);
            }
        }
    }

    return v[N - 1][W];
}

}
