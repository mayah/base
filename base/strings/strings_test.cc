#include "base/strings/strings.h"

#include <gtest/gtest.h>

TEST(StringsTest, concat)
{
    EXPECT_EQ("", strings::concat("", ""));
    EXPECT_EQ("a", strings::concat("a", ""));
    EXPECT_EQ("b", strings::concat("", "b"));
    EXPECT_EQ("ab", strings::concat("a", "b"));

    EXPECT_EQ("abc", strings::concat("a", "b", "c"));
    EXPECT_EQ("ac", strings::concat("a", "", "c"));
}

TEST(StringsTest, hasPrefix)
{
    EXPECT_TRUE(strings::hasPrefix("a", ""));
    EXPECT_TRUE(strings::hasPrefix("ab", "a"));
    EXPECT_TRUE(strings::hasPrefix("ab", "ab"));

    EXPECT_FALSE(strings::hasPrefix("ab", "ac"));
    EXPECT_FALSE(strings::hasPrefix("", "ac"));
}

TEST(StringsTest, hasSuffix)
{
    EXPECT_TRUE(strings::hasSuffix("a", ""));
    EXPECT_TRUE(strings::hasSuffix("ab", "b"));
    EXPECT_TRUE(strings::hasSuffix("ab", "ab"));

    EXPECT_FALSE(strings::hasSuffix("ab", "cab"));
    EXPECT_FALSE(strings::hasSuffix("", "ab"));
}

TEST(StringsTest, repeat)
{
    EXPECT_EQ("", strings::repeat("a", 0));
    EXPECT_EQ("aaa", strings::repeat("a", 3));
    EXPECT_EQ("ababab", strings::repeat("ab", 3));
}

TEST(StringsTest, trimSpace)
{
    EXPECT_EQ("", strings::trimSpace(""));
    EXPECT_EQ("a", strings::trimSpace("a"));
    EXPECT_EQ("a", strings::trimSpace("  a"));
    EXPECT_EQ("a", strings::trimSpace("a  "));
    EXPECT_EQ("a", strings::trimSpace("  a  "));
    EXPECT_EQ("a  a", strings::trimSpace("  a  a  "));
}
