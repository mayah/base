#include "math/prime.h"

#include <vector>

namespace math {

std::vector<int> eratosthenes(int N)
{
    std::vector<bool> flags(N, true);
    flags[0] = flags[1] = false;

    for (int i = 2; i * i < N; ++i) {
        if (flags[i]) {
            for (int j = i + i; j < N; j += i) {
                flags[j] = false;
            }
        }
    }

    std::vector<int> ps;
    for (int i = 2; i < N; ++i) {
        if (flags[i]) { ps.push_back(i); }
    }

    return ps;
}

} // namespace math
