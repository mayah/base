#include "base/strings/ascii_ctype.h"

#include <gtest/gtest.h>

TEST(AsciiCtypeTest, isspace_ascii)
{
    EXPECT_TRUE(strings::isspace_ascii(' '));
    EXPECT_TRUE(strings::isspace_ascii('\t'));
    EXPECT_TRUE(strings::isspace_ascii('\r'));
    EXPECT_TRUE(strings::isspace_ascii('\n'));
    EXPECT_TRUE(strings::isspace_ascii('\v'));
    EXPECT_TRUE(strings::isspace_ascii('\f'));

    EXPECT_FALSE(strings::isspace_ascii('\0'));
    EXPECT_FALSE(strings::isspace_ascii('@'));
    EXPECT_FALSE(strings::isspace_ascii('_'));
}
