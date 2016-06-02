#include "base/containers/matrix.h"

#include <gtest/gtest.h>

TEST(MatrixTest, basic)
{
    base::Matrix<int> m(3, 7);

    EXPECT_EQ(3, m.height());
    EXPECT_EQ(7, m.width());

    m(0, 0) = 0;
    m(0, 1) = 3;
    m(2, 6) = 9;

    EXPECT_EQ(0, m(0, 0));
    EXPECT_EQ(3, m(0, 1));
    EXPECT_EQ(9, m(2, 6));
}
