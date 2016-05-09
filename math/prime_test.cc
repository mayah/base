#include "math/prime.h"

#include <gtest/gtest.h>

TEST(PrimeTest, eratosthenes)
{
    std::vector<int> ps = math::eratosthenes(11);

    EXPECT_EQ(4U, ps.size());

    EXPECT_EQ(2, ps[0]);
    EXPECT_EQ(3, ps[1]);
    EXPECT_EQ(5, ps[2]);
    EXPECT_EQ(7, ps[3]);
}
