#include "base/containers/ring_buffer.h"

#include <gtest/gtest.h>

TEST(RingBufferTest, push_back)
{
    base::RingBuffer<int> rb(10);
    EXPECT_EQ(0U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(10U, rb.available());

    rb.push_back(0);

    EXPECT_EQ(1U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(9U, rb.available());
    EXPECT_EQ(0, rb.front());
    EXPECT_EQ(0, rb.back());

    rb.push_back(1);

    EXPECT_EQ(2U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(8U, rb.available());
    EXPECT_EQ(0, rb.front());
    EXPECT_EQ(1, rb.back());

    rb.push_back(2);

    EXPECT_EQ(3U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(7U, rb.available());
    EXPECT_EQ(0, rb.front());
    EXPECT_EQ(2, rb.back());
}

TEST(RingBufferTest, push_front)
{
    base::RingBuffer<int> rb(10);
    EXPECT_EQ(0U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(10U, rb.available());

    rb.push_front(0);

    EXPECT_EQ(1U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(9U, rb.available());
    EXPECT_EQ(0, rb.front());
    EXPECT_EQ(0, rb.back());

    rb.push_front(1);

    EXPECT_EQ(2U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(8U, rb.available());
    EXPECT_EQ(1, rb.front());
    EXPECT_EQ(0, rb.back());

    rb.push_front(2);

    EXPECT_EQ(3U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(7U, rb.available());
    EXPECT_EQ(2, rb.front());
    EXPECT_EQ(0, rb.back());
}

TEST(RingBufferTest, basic)
{
    base::RingBuffer<int> rb(10);
    EXPECT_EQ(0U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(10U, rb.available());

    rb.push_back(0);
    rb.push_back(1);
    rb.push_front(2);
    rb.push_front(3);

    EXPECT_EQ(4U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(6U, rb.available());

    // The content should be "3, 2, 0, 1".

    EXPECT_EQ(3, rb.front());
    rb.pop_front();
    EXPECT_EQ(2, rb.front());
    rb.pop_front();
    EXPECT_EQ(0, rb.front());
    rb.pop_front();
    EXPECT_EQ(1, rb.front());
    rb.pop_front();

    EXPECT_EQ(0U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(10U, rb.available());
}

TEST(RingBufferTest, full)
{
    base::RingBuffer<int> rb(10);

    for (int i = 0; i < 10; ++i) {
        rb.push_back(i);
        EXPECT_EQ(static_cast<size_t>(i + 1), rb.size());
        EXPECT_EQ(10U, rb.capacity());
        EXPECT_EQ(static_cast<size_t>(10 - i - 1), rb.available());
    }

    rb.clear();
    EXPECT_EQ(0U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(10U, rb.available());

    for (int i = 0; i < 10; ++i) {
        rb.push_front(i);
        EXPECT_EQ(static_cast<size_t>(i + 1), rb.size());
        EXPECT_EQ(10U, rb.capacity());
        EXPECT_EQ(static_cast<size_t>(10 - i - 1), rb.available());
    }

    rb.clear();
    EXPECT_EQ(0U, rb.size());
    EXPECT_EQ(10U, rb.capacity());
    EXPECT_EQ(10U, rb.available());
}
