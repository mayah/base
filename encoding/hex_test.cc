#include "encoding/hex.h"

#include <gtest/gtest.h>

#include "base/macros.h"

TEST(EncodingHexTest, fromHexChar)
{
    EXPECT_EQ(0, encoding::hex::fromHexChar('0'));
    EXPECT_EQ(9, encoding::hex::fromHexChar('9'));
    EXPECT_EQ(10, encoding::hex::fromHexChar('A'));
    EXPECT_EQ(10, encoding::hex::fromHexChar('a'));
    EXPECT_EQ(15, encoding::hex::fromHexChar('F'));
    EXPECT_EQ(15, encoding::hex::fromHexChar('f'));
}

TEST(EncodingHexTest, encode)
{
    unsigned char buf[] {
        0x00, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xFF
    };

    EXPECT_EQ("00123456789ABCDEFF", encoding::hex::encode(buf, ARRAY_SIZE(buf)));
    EXPECT_EQ("", encoding::hex::encode(buf, 0));
}
