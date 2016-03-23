#include "base/strings/join.h"

#include <gtest/gtest.h>

TEST(JoinTest, join)
{
    EXPECT_EQ("", strings::join({}, ","));
    EXPECT_EQ("a", strings::join({"a"}, ","));
    EXPECT_EQ("a,b", strings::join({"a", "b"}, ","));
    EXPECT_EQ("ab", strings::join({"a", "b"}, ""));
}
