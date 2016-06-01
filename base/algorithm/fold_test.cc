#include "base/algorithm/fold.h"

#include <gtest/gtest.h>

TEST(FoldTest, fold)
{
    std::vector<int> vs = { 1, 2, 3, 4, 5 };

    int sum = base::fold_left(vs.begin(), vs.end(), 0, [](int x, int y) { return x + y; });
    EXPECT_EQ(15, sum);
}
