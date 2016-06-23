#include "base/containers/linked_map.h"

#include <gtest/gtest.h>

TEST(LinkedMapTest, basic)
{
    base::LinkedMap<int, int> lm;

    EXPECT_TRUE(lm.empty());
    EXPECT_EQ(0U, lm.size());

    EXPECT_TRUE(lm.insert(std::make_pair(0, 0)).second);
    EXPECT_TRUE(lm.insert(std::make_pair(2, 2)).second);
    EXPECT_TRUE(lm.insert(std::make_pair(1, 1)).second);

    EXPECT_FALSE(lm.empty());
    EXPECT_EQ(3U, lm.size());

    EXPECT_FALSE(lm.insert(std::make_pair(0, 5)).second);
    EXPECT_FALSE(lm.insert(std::make_pair(2, 5)).second);
    EXPECT_FALSE(lm.insert(std::make_pair(1, 5)).second);

    EXPECT_FALSE(lm.empty());
    EXPECT_EQ(3U, lm.size());

    EXPECT_EQ(lm.find(-1), lm.end());
    EXPECT_EQ(lm.find(3), lm.end());
    EXPECT_EQ(0, lm.find(0)->second);
    EXPECT_EQ(1, lm.find(1)->second);
    EXPECT_EQ(2, lm.find(2)->second);

    std::vector<int> keys;
    for (const auto& entry : lm) {
        keys.push_back(entry.first);
    }
    EXPECT_EQ(3U, keys.size());
    EXPECT_EQ(0, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(1, keys[2]);
}
