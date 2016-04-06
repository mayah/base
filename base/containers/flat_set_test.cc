#include "base/containers/flat_set.h"

#include <gtest/gtest.h>

TEST(FlatSetTest, basic)
{
    base::FlatSet<int> fs;

    EXPECT_TRUE(fs.empty());
    EXPECT_EQ(0U, fs.size());

    EXPECT_TRUE(fs.insert(3).second);

    EXPECT_FALSE(fs.empty());
    EXPECT_EQ(1U, fs.size());

    EXPECT_TRUE(fs.insert(1).second);
    EXPECT_EQ(5, *fs.insert(5).first);

    EXPECT_FALSE(fs.empty());
    EXPECT_EQ(3U, fs.size());

    EXPECT_EQ(fs.end(), fs.find(2));
    EXPECT_EQ(fs.end(), fs.find(0));

    EXPECT_EQ(1, *fs.find(1));
    EXPECT_EQ(3, *fs.find(3));
    EXPECT_EQ(5, *fs.find(5));

    EXPECT_EQ(1, *fs.insert(1).first);
    EXPECT_FALSE(fs.insert(1).second);
    EXPECT_EQ(5, *fs.insert(5).first);
    EXPECT_FALSE(fs.insert(5).second);

    EXPECT_FALSE(fs.empty());
    EXPECT_EQ(3U, fs.size());
}
