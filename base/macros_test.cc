#include "base/macros.h"

#include <gtest/gtest.h>

using namespace std;

TEST(MacrosTest, size)
{
    char cbuf[1024];
    int ibuf[23];

    EXPECT_EQ(1024U, ARRAY_SIZE(cbuf));
    EXPECT_EQ(23U, ARRAY_SIZE(ibuf));
}
