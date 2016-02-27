#include "math/gauss.h"

#include <gtest/gtest.h>

TEST(GaussTest, solve)
{
    //  x +  y = 3
    // 2x + 5y = 9
    // --> x = 2, y = 1

    std::vector<std::vector<double>> a(2, std::vector<double>(2));
    std::vector<double> b(2);
    std::vector<double> x(2);

    a[0][0] = 1; a[0][1] = 1;
    a[1][0] = 2; a[1][1] = 5;

    b[0] = 3; b[1] = 9;

    EXPECT_TRUE(math::gauss(a, b, &x));

    EXPECT_DOUBLE_EQ(2, x[0]);
    EXPECT_DOUBLE_EQ(1, x[1]);
}
