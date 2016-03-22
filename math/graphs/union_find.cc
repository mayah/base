#include "math/graphs/union_find.h"

#include "base/containers/vectors.h"

namespace graphs {

UnionFind::UnionFind(int n) :
    vs_(vectors::range(0, n)),
    cardinal_(n)
{
}

int UnionFind::find(int i)
{
    if (vs_[i] == i)
        return i;

    int x = find(vs_[i]);
    vs_[i] = x;
    return x;
}

void UnionFind::unify(int a, int b)
{
    int aa = find(a);
    int bb = find(b);
    if (bb != aa) {
        vs_[bb] = aa;
        --cardinal_;
    }
}

} // namespace graphs
