#ifndef MATH_GRAPHS_UNION_FIND_H_
#define MATH_GRAPHS_UNION_FIND_H_

#include <vector>

namespace graphs {

// Implements union-find algorithm.
// Not thread safe.
class UnionFind {
public:
    explicit UnionFind(int n);

    int cardinal() const { return cardinal_; }

    int find(int i);
    void unify(int a, int b);

private:
    std::vector<int> vs_;
    int cardinal_;
};

} // namespace graphs

#endif // MATH_GRAPHS_UNION_FIND_H_
