#include "base/time/time.h"

#include <gtest/gtest.h>

TEST(TimeTest, now)
{
    base::Time t;
    EXPECT_EQ(std::chrono::system_clock::time_point(), t.time_point());
}
