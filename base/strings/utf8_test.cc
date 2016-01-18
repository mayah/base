#include "base/strings/utf8.h"

#include <gtest/gtest.h>

TEST(UTF8Test, to_utf8)
{
    std::string s;
    s += '\0';
    EXPECT_EQ(s, strings::to_utf8(0x0U));

    EXPECT_EQ("\u0001", strings::to_utf8(0x1U));
    EXPECT_EQ("\u0080", strings::to_utf8(0x80U));
    EXPECT_EQ("\u0800", strings::to_utf8(0x800U));
    EXPECT_EQ("\U00010000", strings::to_utf8(0x10000U));

    EXPECT_EQ("\u007F", strings::to_utf8(0x7FU));
    EXPECT_EQ("\u07FF", strings::to_utf8(0x7FFU));
    EXPECT_EQ("\uFFFF", strings::to_utf8(0xFFFFU));
    EXPECT_EQ("\U0010FFFF", strings::to_utf8(0x10FFFFU));

    // Don't allow 0x110000U.
    EXPECT_EQ("", strings::to_utf8(0x110000U));
}
