#include "base/containers/slice.h"

#include <vector>

#include <gtest/gtest.h>

#include "base/macros.h"

using namespace std;

TEST(SliceTest, init)
{
    int vs[] { 0, 1, 2, 3, 4, 5, 6 };
    base::Slice<int> ss(vs, ARRAY_SIZE(vs));

    EXPECT_EQ(7U, ss.size());
    EXPECT_EQ(0, ss[0]);
    EXPECT_EQ(6, ss[6]);

    ss = ss.subseq(1, 3);
    EXPECT_EQ(3U, ss.size());
    EXPECT_EQ(1, ss[0]);
    EXPECT_EQ(3, ss[2]);
}

TEST(SliceTest, init_with_vector)
{
    vector<int> vs { 0, 1, 2, 3, 4, 5, 6 };
    base::Slice<int> ss(vs);

    EXPECT_EQ(7U, ss.size());
    EXPECT_EQ(0, ss[0]);
    EXPECT_EQ(6, ss[6]);

    ss = ss.subseq(1, 3);
    EXPECT_EQ(3U, ss.size());
    EXPECT_EQ(1, ss[0]);
    EXPECT_EQ(3, ss[2]);
}
