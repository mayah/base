#include "base/containers/byte_buffer.h"

#include <gtest/gtest.h>

TEST(ByteBufferTest, basic)
{
    base::ByteBuffer buffer(128);
    EXPECT_EQ(0U, buffer.size());
    EXPECT_LE(128U, buffer.capacity());
}

TEST(ByteBufferTest, put)
{
    base::ByteBuffer buffer(128);
    buffer.push_back('a');
    buffer.push_back('b');

    EXPECT_EQ(2U, buffer.size());
    EXPECT_EQ('a', buffer[0]);
    EXPECT_EQ('b', buffer[1]);
}
