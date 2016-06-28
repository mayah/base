#include "base/bits/count.h"

#include <gtest/gtest.h>

TEST(PopCountTest, popcount32)
{
    EXPECT_EQ(1, base::popcount32(1));
    EXPECT_EQ(1, base::popcount32(2));
    EXPECT_EQ(2, base::popcount32(3));
    EXPECT_EQ(1, base::popcount32(4));
    EXPECT_EQ(2, base::popcount32(5));
    EXPECT_EQ(2, base::popcount32(6));
    EXPECT_EQ(3, base::popcount32(7));

    EXPECT_EQ(1, base::popcount32(8));
    EXPECT_EQ(2, base::popcount32(9));
    EXPECT_EQ(2, base::popcount32(10));
    EXPECT_EQ(3, base::popcount32(11));
    EXPECT_EQ(2, base::popcount32(12));
    EXPECT_EQ(3, base::popcount32(13));
    EXPECT_EQ(3, base::popcount32(14));
    EXPECT_EQ(4, base::popcount32(15));

    EXPECT_EQ(32, base::popcount32(0xFFFFFFFFU));
    EXPECT_EQ(0+1+1+2+1+2+2+3, base::popcount32(0x01234567U));
    EXPECT_EQ(1+2+2+3+2+3+3+4, base::popcount32(0x89ABCDEFU));
}

TEST(PopCountTest, popcount64)
{
    EXPECT_EQ(1, base::popcount64(1));
    EXPECT_EQ(1, base::popcount64(2));
    EXPECT_EQ(2, base::popcount64(3));
    EXPECT_EQ(1, base::popcount64(4));
    EXPECT_EQ(2, base::popcount64(5));
    EXPECT_EQ(2, base::popcount64(6));
    EXPECT_EQ(3, base::popcount64(7));

    EXPECT_EQ(1, base::popcount64(8));
    EXPECT_EQ(2, base::popcount64(9));
    EXPECT_EQ(2, base::popcount64(10));
    EXPECT_EQ(3, base::popcount64(11));
    EXPECT_EQ(2, base::popcount64(12));
    EXPECT_EQ(3, base::popcount64(13));
    EXPECT_EQ(3, base::popcount64(14));
    EXPECT_EQ(4, base::popcount64(15));

    EXPECT_EQ(64, base::popcount64(0xFFFFFFFFFFFFFFFFLLU));
    EXPECT_EQ(0+1+1+2+1+2+2+3+1+2+2+3+2+3+3+4, base::popcount64(0x0123456789ABCDEFU));
}
