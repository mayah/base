#include "base/strings/join.h"

#include <gtest/gtest.h>
#include <set>

TEST(JoinTest, join)
{
    EXPECT_EQ("", strings::join({}, ","));
    EXPECT_EQ("a", strings::join({"a"}, ","));
    EXPECT_EQ("a,b", strings::join({"a", "b"}, ","));
    EXPECT_EQ("ab", strings::join({"a", "b"}, ""));
}

TEST(JoinTest, join_with_iterator)
{
    std::set<std::string> ss {
        "a", "b", "c"
    };

    EXPECT_EQ("a,b,c", strings::join(ss.begin(), ss.end(), ","));
}
