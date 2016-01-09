#include "base/containers/vectors.h"

#include <gtest/gtest.h>

TEST(VectorsTest, init)
{
    auto v = vectors::init<int>(10, [](size_t i) -> int {
        return static_cast<int>(i) * 2;
    });

    EXPECT_EQ(10U, v.size());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(18, v[9]);
}
