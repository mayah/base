#include "base/containers/flat_map.h"

#include <vector>
#include <gtest/gtest.h>

TEST(FlatMapTest, basic)
{
    base::FlatMap<int, int> fm;

    EXPECT_TRUE(fm.empty());
    EXPECT_EQ(0, fm.size());

    {
        auto p = fm.insert(std::make_pair(0, 10));
        EXPECT_TRUE(p.second);
        EXPECT_EQ(0, p.first->first);
        EXPECT_EQ(10, p.first->second);

        EXPECT_EQ(1, fm.size());
    }
    {
        auto p = fm.insert(std::make_pair(0, 20));
        EXPECT_FALSE(p.second);
        EXPECT_EQ(0, p.first->first);
        EXPECT_EQ(10, p.first->second);

        EXPECT_EQ(1, fm.size());
    }

    EXPECT_TRUE(fm.insert(std::make_pair(1, 30)).second);
    EXPECT_TRUE(fm.insert(std::make_pair(-1, 40)).second);
    EXPECT_TRUE(fm.insert(std::make_pair(2, 50)).second);
    EXPECT_TRUE(fm.insert(std::make_pair(-2, 60)).second);

    EXPECT_EQ(5U, fm.size());

    {
        std::vector<std::pair<int, int>> entries;
        for (const auto& entry : fm) {
            entries.push_back(entry);
        }

        EXPECT_EQ(5U, entries.size());
        EXPECT_EQ(-2, entries[0].first);
        EXPECT_EQ(-1, entries[1].first);
        EXPECT_EQ(-0, entries[2].first);
        EXPECT_EQ(1, entries[3].first);
        EXPECT_EQ(2, entries[4].first);
    }

    EXPECT_EQ(fm.find(-3), fm.end());
    EXPECT_EQ(fm.find(-2)->second, 60);
    EXPECT_EQ(fm.find(-1)->second, 40);
    EXPECT_EQ(fm.find(-0)->second, 10);
    EXPECT_EQ(fm.find(1)->second, 30);
    EXPECT_EQ(fm.find(2)->second, 50);
    EXPECT_EQ(fm.find(3), fm.end());
}
