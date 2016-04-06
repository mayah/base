#include "base/containers/small_int_set.h"

#include <gtest/gtest.h>

TEST(SmallIntSetTest, basic)
{
    base::SmallIntSet s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0, s.size());

    s.set(0);
    s.set(1);
    s.set(5);
    s.set(8);
    s.set(16);
    s.set(31);
    s.set(31);
    s.set(63);

    EXPECT_EQ(7, s.size());

    s.unset(8);
    EXPECT_EQ(6, s.size());

    EXPECT_EQ(0, s.smallest());
    s.remove_smallest();

    EXPECT_EQ(1, s.smallest());
    s.remove_smallest();

    EXPECT_EQ(5, s.smallest());
    s.remove_smallest();

    EXPECT_EQ(16, s.smallest());
    s.remove_smallest();

    EXPECT_EQ(31, s.smallest());
    s.remove_smallest();

    EXPECT_EQ(63, s.smallest());
    s.remove_smallest();

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0, s.size());
}
