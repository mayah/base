#include "base/containers/assoc_map.h"

#include <gtest/gtest.h>

TEST(AssocMapTest, basic)
{
    base::AssocMap<int, int> kvs;
    EXPECT_TRUE(kvs.empty());
    EXPECT_EQ(0U, kvs.size());

    kvs.insert(std::make_pair(0, 1));
    kvs.insert(std::make_pair(1, 10));
    kvs.insert(std::make_pair(2, 100));

    EXPECT_FALSE(kvs.empty());
    EXPECT_EQ(3U, kvs.size());

    auto p = kvs.insert(std::make_pair(3, 1000));
    EXPECT_EQ(3, p.first->first);
    EXPECT_EQ(1000, p.first->second);
    EXPECT_TRUE(p.second);

    p = kvs.insert(std::make_pair(3, -1000));
    EXPECT_EQ(3, p.first->first);
    EXPECT_EQ(1000, p.first->second);
    EXPECT_FALSE(p.second);
}
