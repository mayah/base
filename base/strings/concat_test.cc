#include "base/strings/concat.h"

#include <gtest/gtest.h>

TEST(ConcatTest, concat)
{
    EXPECT_EQ("", strings::concat("", ""));
    EXPECT_EQ("a", strings::concat("a", ""));
    EXPECT_EQ("b", strings::concat("", "b"));
    EXPECT_EQ("ab", strings::concat("a", "b"));

    EXPECT_EQ("abc", strings::concat("a", "b", "c"));
    EXPECT_EQ("ac", strings::concat("a", "", "c"));

    EXPECT_EQ("abc123", strings::concat("a", "b", "c", 1, 2, 3));
}
