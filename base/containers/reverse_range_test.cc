#include "base/containers/reverse_range.h"

#include <gtest/gtest.h>

using namespace std;

TEST(ReverseRangeTest, reverse_range)
{
    vector<int> vs { 1, 2, 3, 4, 5 };
    vector<int> results;
    for (const auto& v : base::reverse_range(vs)) {
        results.push_back(v);
    }

    EXPECT_EQ(5UL, results.size());
    EXPECT_EQ(5, results[0]);
    EXPECT_EQ(1, results[4]);
}

TEST(ReverseRangeTest, reverse_range_array)
{
    int vs[] { 1, 2, 3, 4, 5 };
    vector<int> results;
    for (const auto& v : base::reverse_range(vs)) {
        results.push_back(v);
    }

    EXPECT_EQ(5UL, results.size());
    EXPECT_EQ(5, results[0]);
    EXPECT_EQ(1, results[4]);
}
