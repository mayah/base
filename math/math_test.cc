#include "math/math.h"

#include <gtest/gtest.h>

TEST(MathTest, gcd)
{
    EXPECT_EQ(3, math::gcd(3, 3 * 5));
    EXPECT_EQ(3, math::gcd(3 * 7, 3 * 5));
}

TEST(MathTest, exgcd)
{
    int a, b;
    EXPECT_EQ(3, math::exgcd(3, 3 * 5, &a, &b));
    EXPECT_EQ(1, a);
    EXPECT_EQ(0, b);
    EXPECT_EQ(3, 3 * a + 5 * b);

    EXPECT_EQ(3, math::exgcd(3 * 7, 3 * 5, &a, &b));
    EXPECT_EQ(-2, a);
    EXPECT_EQ(3, b);
    EXPECT_EQ(3, 3 * 7 * a + 3 * 5 * b);
}
