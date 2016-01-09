#include "base/strings/split.h"

#include <gtest/gtest.h>

TEST(StringsSplitTest, split)
{
    std::vector<std::string> s = strings::split("A, B,, C", ",");
    EXPECT_EQ(4UL, s.size());
    EXPECT_EQ("A", s[0]);
    EXPECT_EQ(" B", s[1]);
    EXPECT_EQ("", s[2]);
    EXPECT_EQ(" C", s[3]);
}

TEST(StringsSplitTest, split_AllowEmpty)
{
    std::vector<std::string> s = strings::split("A, B,, C", ",", strings::AllowEmpty());
    EXPECT_EQ(4UL, s.size());
    EXPECT_EQ("A", s[0]);
    EXPECT_EQ(" B", s[1]);
    EXPECT_EQ("", s[2]);
    EXPECT_EQ(" C", s[3]);
}

TEST(StringsSplitTest, split_SkipEmpty)
{
    std::vector<std::string> s = strings::split("A, B,, C", ",", strings::SkipEmpty());
    EXPECT_EQ(3UL, s.size());
    EXPECT_EQ("A", s[0]);
    EXPECT_EQ(" B", s[1]);
    EXPECT_EQ(" C", s[2]);
}
