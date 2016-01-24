#include "math/math.h"

#include <gtest/gtest.h>

TEST(MathTest, gcd)
{
    EXPECT_EQ(3, math::gcd(3, 3 * 5));
    EXPECT_EQ(3, math::gcd(3 * 7, 3 * 5));
}
