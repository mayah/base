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

TEST(StringsTest, join)
{
    EXPECT_EQ("", strings::join({}, ","));
    EXPECT_EQ("a", strings::join({"a"}, ","));
    EXPECT_EQ("a,b", strings::join({"a", "b"}, ","));
    EXPECT_EQ("ab", strings::join({"a", "b"}, ""));
}

TEST(StringsTest, has_prefix)
{
    EXPECT_TRUE(strings::has_prefix("a", ""));
    EXPECT_TRUE(strings::has_prefix("ab", "a"));
    EXPECT_TRUE(strings::has_prefix("ab", "ab"));

    EXPECT_FALSE(strings::has_prefix("ab", "ac"));
    EXPECT_FALSE(strings::has_prefix("", "ac"));
}

TEST(StringsTest, has_suffix)
{
    EXPECT_TRUE(strings::has_suffix("a", ""));
    EXPECT_TRUE(strings::has_suffix("ab", "b"));
    EXPECT_TRUE(strings::has_suffix("ab", "ab"));

    EXPECT_FALSE(strings::has_suffix("ab", "cab"));
    EXPECT_FALSE(strings::has_suffix("", "ab"));
}

TEST(StringsTest, repeat)
{
    EXPECT_EQ("", strings::repeat("a", 0));
    EXPECT_EQ("aaa", strings::repeat("a", 3));
    EXPECT_EQ("ababab", strings::repeat("ab", 3));
}

TEST(StringsTest, trim_left)
{
    EXPECT_EQ("abc", strings::trim_left("abc", ' '));
    EXPECT_EQ("bc", strings::trim_left("abc", 'a'));
    EXPECT_EQ("bc", strings::trim_left("aaaabc", 'a'));
    EXPECT_EQ("abc", strings::trim_left("abc", 'b'));
    EXPECT_EQ("abc", strings::trim_left("abc", 'c'));

    EXPECT_EQ("abc", strings::trim_left("abc", ""));
    EXPECT_EQ("bc", strings::trim_left("abc", "a"));
    EXPECT_EQ("c", strings::trim_left("abc", "ba"));
    EXPECT_EQ("", strings::trim_left("abc", "abc"));
    EXPECT_EQ("abc", strings::trim_left("abc", "bc"));
    EXPECT_EQ("abc", strings::trim_left("abc", "d"));
}

TEST(StringsTest, trim_right)
{
    EXPECT_EQ("abc", strings::trim_right("abc", ' '));
    EXPECT_EQ("abc", strings::trim_right("abc", 'a'));
    EXPECT_EQ("abc", strings::trim_right("abc", 'b'));
    EXPECT_EQ("ab", strings::trim_right("abc", 'c'));
    EXPECT_EQ("ab", strings::trim_right("abcc", 'c'));

    EXPECT_EQ("abc", strings::trim_right("abc", ""));
    EXPECT_EQ("abc", strings::trim_right("abc", "a"));
    EXPECT_EQ("abc", strings::trim_right("abc", "ba"));
    EXPECT_EQ("", strings::trim_right("abc", "abc"));
    EXPECT_EQ("a", strings::trim_right("abc", "bc"));
    EXPECT_EQ("abc", strings::trim_right("abc", "d"));
}

TEST(StringsTest, trim_space)
{
    EXPECT_EQ("", strings::trim_space(""));
    EXPECT_EQ("a", strings::trim_space("a"));
    EXPECT_EQ("a", strings::trim_space("  a"));
    EXPECT_EQ("a", strings::trim_space("a  "));
    EXPECT_EQ("a", strings::trim_space("  a  "));
    EXPECT_EQ("a  a", strings::trim_space("  a  a  "));
}

TEST(StringsTest, trim_prefix)
{
    EXPECT_EQ("abc", strings::trim_prefix("abc", ""));
    EXPECT_EQ("bc", strings::trim_prefix("abc", "a"));
    EXPECT_EQ("c", strings::trim_prefix("abc", "ab"));
    EXPECT_EQ("", strings::trim_prefix("abc", "abc"));
    EXPECT_EQ("abc", strings::trim_prefix("abc", "abcd"));
    EXPECT_EQ("abc", strings::trim_prefix("abc", "bcd"));
}

TEST(StringsTest, trim_suffix)
{
    EXPECT_EQ("abc", strings::trim_suffix("abc", ""));
    EXPECT_EQ("ab", strings::trim_suffix("abc", "c"));
    EXPECT_EQ("a", strings::trim_suffix("abc", "bc"));
    EXPECT_EQ("", strings::trim_suffix("abc", "abc"));
    EXPECT_EQ("abc", strings::trim_suffix("abc", "abcd"));
    EXPECT_EQ("abc", strings::trim_suffix("abc", "bce"));
}

TEST(StringsTest, remove)
{
    EXPECT_EQ("", strings::remove("", 'c'));
    EXPECT_EQ("ababABCABC", strings::remove("abcabcABCABC", 'c'));
}

TEST(StringsTest, to_lower_ASCII)
{
    EXPECT_EQ('a', strings::to_lower_ASCII('A'));
    EXPECT_EQ('a', strings::to_lower_ASCII('a'));
    EXPECT_EQ('z', strings::to_lower_ASCII('Z'));
    EXPECT_EQ('z', strings::to_lower_ASCII('z'));
    EXPECT_EQ('0', strings::to_lower_ASCII('0'));
    EXPECT_EQ('9', strings::to_lower_ASCII('9'));

    EXPECT_EQ("abcdefgh", strings::to_lower_ASCII("ABCDefgh"));
}

TEST(StringsTest, to_upper_ASCII)
{
    EXPECT_EQ('A', strings::to_upper_ASCII('A'));
    EXPECT_EQ('A', strings::to_upper_ASCII('a'));
    EXPECT_EQ('Z', strings::to_upper_ASCII('Z'));
    EXPECT_EQ('Z', strings::to_upper_ASCII('z'));
    EXPECT_EQ('0', strings::to_upper_ASCII('0'));
    EXPECT_EQ('9', strings::to_upper_ASCII('9'));

    EXPECT_EQ("ABCDEFGH", strings::to_upper_ASCII("ABCDefgh"));
}
