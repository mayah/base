#include "base/strings/strings.h"

#include <gtest/gtest.h>

TEST(strings_test, hasPrefix)
{
    EXPECT_TRUE(strings::hasPrefix("a", ""));
    EXPECT_TRUE(strings::hasPrefix("ab", "a"));
    EXPECT_TRUE(strings::hasPrefix("ab", "ab"));

    EXPECT_FALSE(strings::hasPrefix("ab", "ac"));
    EXPECT_FALSE(strings::hasPrefix("", "ac"));
}

TEST(strings_test, hasSuffix)
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
