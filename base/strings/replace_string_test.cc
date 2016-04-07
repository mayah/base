#include "base/strings/replace_string.h"

#include <gtest/gtest.h>

TEST(ReplaceStringTest, replace)
{
    EXPECT_EQ("", strings::replace_string("", "", "", strings::OneOrAll::ONE));
    EXPECT_EQ("aaa", strings::replace_string("aaa", "", "bbb", strings::OneOrAll::ONE));

    EXPECT_EQ("baa", strings::replace_string("aaa", "a", "b", strings::OneOrAll::ONE));
    EXPECT_EQ("aeeec", strings::replace_string("abc", "b", "eee", strings::OneOrAll::ONE));
}

TEST(ReplaceStringTest, replace_all)
{
    EXPECT_EQ("", strings::replace_string("", "", "", strings::OneOrAll::ALL));
    EXPECT_EQ("aaa", strings::replace_string("aaa", "", "bbb", strings::OneOrAll::ALL));

    EXPECT_EQ("bbb", strings::replace_string("aaa", "a", "b", strings::OneOrAll::ALL));
    EXPECT_EQ("aeeeeeebc", strings::replace_string("abababc", "ba", "eee", strings::OneOrAll::ALL));
}
