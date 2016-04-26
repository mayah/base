#include "base/strings/strings.h"

#include <gtest/gtest.h>

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

TEST(StringsTest, pad_left)
{
    EXPECT_EQ("", strings::pad_left("", 0, '@'));
    EXPECT_EQ("@", strings::pad_left("", 1, '@'));
    EXPECT_EQ("@@", strings::pad_left("", 2, '@'));

    EXPECT_EQ("aa", strings::pad_left("aa", 0, '@'));
    EXPECT_EQ("aa", strings::pad_left("aa", 1, '@'));
    EXPECT_EQ("aa", strings::pad_left("aa", 2, '@'));
    EXPECT_EQ("@aa", strings::pad_left("aa", 3, '@'));
    EXPECT_EQ("@@aa", strings::pad_left("aa", 4, '@'));
}

TEST(StringTest, pad_right)
{
    EXPECT_EQ("", strings::pad_right("", 0, '@'));
    EXPECT_EQ("@", strings::pad_right("", 1, '@'));
    EXPECT_EQ("@@", strings::pad_right("", 2, '@'));

    EXPECT_EQ("aa", strings::pad_right("aa", 0, '@'));
    EXPECT_EQ("aa", strings::pad_right("aa", 1, '@'));
    EXPECT_EQ("aa", strings::pad_right("aa", 2, '@'));
    EXPECT_EQ("aa@", strings::pad_right("aa", 3, '@'));
    EXPECT_EQ("aa@@", strings::pad_right("aa", 4, '@'));
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

TEST(StringsTest, tolower_ascii)
{
    EXPECT_EQ("abcdefgh", strings::tolower_ascii("ABCDefgh"));
}

TEST(StringsTest, toupper_ascii)
{
    EXPECT_EQ("ABCDEFGH", strings::toupper_ascii("ABCDefgh"));
}
