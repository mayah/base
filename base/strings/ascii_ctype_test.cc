#include "base/strings/ascii_ctype.h"

#include <gtest/gtest.h>

TEST(ASCIICtypeTest, tolower_ascii)
{
    EXPECT_EQ('a', strings::tolower_ascii('A'));
    EXPECT_EQ('a', strings::tolower_ascii('a'));
    EXPECT_EQ('z', strings::tolower_ascii('Z'));
    EXPECT_EQ('z', strings::tolower_ascii('z'));
    EXPECT_EQ('0', strings::tolower_ascii('0'));
    EXPECT_EQ('9', strings::tolower_ascii('9'));
}

TEST(ASCIICtypeTest, toupper_ascii)
{
    EXPECT_EQ('A', strings::toupper_ascii('A'));
    EXPECT_EQ('A', strings::toupper_ascii('a'));
    EXPECT_EQ('Z', strings::toupper_ascii('Z'));
    EXPECT_EQ('Z', strings::toupper_ascii('z'));
    EXPECT_EQ('0', strings::toupper_ascii('0'));
    EXPECT_EQ('9', strings::toupper_ascii('9'));
}

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
