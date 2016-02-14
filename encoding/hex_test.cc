#include "encoding/hex.h"

#include <gtest/gtest.h>

#include "base/macros.h"

TEST(EncodingHexTest, is_hex_char)
{
    EXPECT_TRUE(encoding::hex::is_hex_char('0'));
    EXPECT_TRUE(encoding::hex::is_hex_char('9'));
    EXPECT_TRUE(encoding::hex::is_hex_char('A'));
    EXPECT_TRUE(encoding::hex::is_hex_char('F'));
    EXPECT_TRUE(encoding::hex::is_hex_char('a'));
    EXPECT_TRUE(encoding::hex::is_hex_char('f'));

    EXPECT_FALSE(encoding::hex::is_hex_char('G'));
    EXPECT_FALSE(encoding::hex::is_hex_char('g'));
    EXPECT_FALSE(encoding::hex::is_hex_char('+'));
    EXPECT_FALSE(encoding::hex::is_hex_char('-'));
    EXPECT_FALSE(encoding::hex::is_hex_char('@'));
    EXPECT_FALSE(encoding::hex::is_hex_char(' '));
}

TEST(EncodingHexTest, from_hex_char)
{
    EXPECT_EQ(0, encoding::hex::from_hex_char('0'));
    EXPECT_EQ(9, encoding::hex::from_hex_char('9'));
    EXPECT_EQ(10, encoding::hex::from_hex_char('A'));
    EXPECT_EQ(10, encoding::hex::from_hex_char('a'));
    EXPECT_EQ(15, encoding::hex::from_hex_char('F'));
    EXPECT_EQ(15, encoding::hex::from_hex_char('f'));
}

TEST(EncodingHexTest, encode)
{
    unsigned char buf[] {
        0x00, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xFF
    };

    EXPECT_EQ("00123456789ABCDEFF", encoding::hex::encode(buf, ARRAY_SIZE(buf)));
    EXPECT_EQ("", encoding::hex::encode(buf, 0));
}

TEST(EncodingHexTest, decode)
{
    std::string s = "00123456789ABCDEFF";
    std::string invalid = "012";

    unsigned char data[1024];

    EXPECT_GT(0, encoding::hex::decode(invalid, data));
}
