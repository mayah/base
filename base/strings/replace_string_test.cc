#include "base/strings/replace_string.h"

#include <gtest/gtest.h>

TEST(ReplaceStringTest, replace)
{
    EXPECT_EQ("", strings::replace_string("", "", "", false));
    EXPECT_EQ("aaa", strings::replace_string("aaa", "", "bbb", false));

    EXPECT_EQ("baa", strings::replace_string("aaa", "a", "b", false));
    EXPECT_EQ("aeeec", strings::replace_string("abc", "b", "eee", false));
}

TEST(ReplaceStringTest, replace_all)
{
    EXPECT_EQ("", strings::replace_string("", "", "", true));
    EXPECT_EQ("aaa", strings::replace_string("aaa", "", "bbb", true));

    EXPECT_EQ("bbb", strings::replace_string("aaa", "a", "b", true));
    EXPECT_EQ("aeeeeeebc", strings::replace_string("abababc", "ba", "eee", true));
}
