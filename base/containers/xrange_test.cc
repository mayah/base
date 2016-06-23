#include "base/containers/xrange.h"

#include <vector>

#include <gtest/gtest.h>

using namespace std;

TEST(RangeTest, range)
{
    vector<int> vs;
    for (int x : base::xrange(0, 10)) {
        vs.push_back(x);
    }

    EXPECT_EQ(10U, vs.size());
    EXPECT_EQ(0, vs[0]);
    EXPECT_EQ(5, vs[5]);
    EXPECT_EQ(9, vs[9]);
}

TEST(RangeTest, range_with_step)
{
    vector<int> vs;
    for (int x : base::xrange(1, 9, 3)) {
        vs.push_back(x);
    }

    EXPECT_EQ(3U, vs.size());
    EXPECT_EQ(1, vs[0]);
    EXPECT_EQ(4, vs[1]);
    EXPECT_EQ(7, vs[2]);
}
