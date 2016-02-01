#include "base/containers/vectors.h"

namespace vectors {

std::vector<int> range(int begin, int end)
{
    if (end < begin)
        return std::vector<int>();

    std::vector<int> vs(end - begin);
    for (int i = begin; i < end; ++i)
        vs[i] = i;
    return vs;
}

} // namespace vectors
