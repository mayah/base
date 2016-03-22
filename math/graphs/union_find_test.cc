#include "math/graphs/union_find.h"

#include <gtest/gtest.h>

TEST(UnionFindTest, basic)
{
    graphs::UnionFind uf(5);
    EXPECT_EQ(5, uf.cardinal());

    uf.unify(0, 1);
    uf.unify(0, 2);

    EXPECT_EQ(uf.find(0), uf.find(1));
    EXPECT_EQ(uf.find(0), uf.find(2));
    EXPECT_EQ(uf.find(1), uf.find(2));

    EXPECT_EQ(3, uf.cardinal());
}
