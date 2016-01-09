#include "encoding/hex.h"

#include <gtest/gtest.h>

#include "base/macros.h"

TEST(EncodingHexTest, encode)
{
    unsigned char buf[] {
        0x00, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xFF
    };

    EXPECT_EQ("00123456789ABCDEFF", encoding::hex::encode(buf, ARRAY_SIZE(buf)));
}
