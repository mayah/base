#include "base/time/fake_clock.h"

#include <gtest/gtest.h>

TEST(FakeClockTest, basic)
{
    base::FakeClock clock;
    clock.set_utc_datetime(2016, 4, 1, 13, 14, 15);

    base::Time t = clock.now();

    struct tm stm;
    ASSERT_TRUE(t.to_tm(&stm));

    EXPECT_EQ(2016, stm.tm_year + 1900);
    EXPECT_EQ(4, stm.tm_mon + 1);
    EXPECT_EQ(1, stm.tm_mday);
    EXPECT_EQ(13, stm.tm_hour);
    EXPECT_EQ(14, stm.tm_min);
    EXPECT_EQ(15, stm.tm_sec);
}
