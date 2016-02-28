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

TEST(VectorsTest, range)
{
    auto a = vectors::range(0, 10);
    auto b = vectors::range(0, 0);
    auto c = vectors::range(10, 0);

    EXPECT_EQ(10U, a.size());
    EXPECT_EQ(0, b.size());
    EXPECT_EQ(0, c.size());
}

TEST(VectorsTest, map)
{
    auto a = vectors::range(0, 10);
    auto b = vectors::map(a, [](int x) -> int { return 2 * x; });

    EXPECT_EQ(10U, b.size());
    EXPECT_EQ(0, b[0]);
    EXPECT_EQ(10, b[5]);
    EXPECT_EQ(18, b[9]);
}

TEST(VectorsTest, map_empty)
{
    std::vector<int> a;
    auto b = vectors::map(a, [](int x) -> int { return 2 * x; });

    EXPECT_EQ(0U, b.size());
}
