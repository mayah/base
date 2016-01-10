#include "encoding/base64.h"

#include <gtest/gtest.h>

TEST(Base64Test, encoding)
{
    EXPECT_EQ("", encoding::base64::encode("", 0));
    EXPECT_EQ("Zg==", encoding::base64::encode("f", 1));
    EXPECT_EQ("Zm8=", encoding::base64::encode("fo", 2));
    EXPECT_EQ("Zm9v", encoding::base64::encode("foo", 3));
    EXPECT_EQ("Zm9vYg==", encoding::base64::encode("foob", 4));
    EXPECT_EQ("Zm9vYmE=", encoding::base64::encode("fooba", 5));
    EXPECT_EQ("Zm9vYmFy", encoding::base64::encode("foobar", 6));
}
