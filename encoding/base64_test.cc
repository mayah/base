#include "encoding/base64.h"

#include <gtest/gtest.h>

TEST(Base64Test, encode)
{
    EXPECT_EQ("", encoding::base64::encode("", 0));
    EXPECT_EQ("Zg==", encoding::base64::encode("f", 1));
    EXPECT_EQ("Zm8=", encoding::base64::encode("fo", 2));
    EXPECT_EQ("Zm9v", encoding::base64::encode("foo", 3));
    EXPECT_EQ("Zm9vYg==", encoding::base64::encode("foob", 4));
    EXPECT_EQ("Zm9vYmE=", encoding::base64::encode("fooba", 5));
    EXPECT_EQ("Zm9vYmFy", encoding::base64::encode("foobar", 6));
}

TEST(Base64Test, decode)
{
    char buf[1024];

    EXPECT_EQ(0, encoding::base64::decode("", buf, 1024));
    EXPECT_EQ(1, encoding::base64::decode("Zg==", buf, 1024));
    EXPECT_EQ(2, encoding::base64::decode("Zm8=", buf, 1024));
    EXPECT_EQ(3, encoding::base64::decode("Zm9v", buf, 1024));
    EXPECT_EQ(4, encoding::base64::decode("Zm9vYg==", buf, 1024));
    EXPECT_EQ(5, encoding::base64::decode("Zm9vYmE=", buf, 1024));
    EXPECT_EQ(6, encoding::base64::decode("Zm9vYmFy", buf, 1024));

    buf[7] = '\0';
    EXPECT_EQ("foobar", std::string(buf));

    EXPECT_EQ(0, encoding::base64::decode("ZgB=", buf, 1024));
    EXPECT_EQ(0, encoding::base64::decode("====", buf, 1024));
    EXPECT_EQ(0, encoding::base64::decode("Z===", buf, 1024));
    EXPECT_EQ(0, encoding::base64::decode("ZZZZ=", buf, 1024));
}
