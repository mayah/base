#ifndef BASE_TIME_FAKE_CLOCK_H_
#define BASE_TIME_FAKE_CLOCK_H_

#include "base/time/clock.h"

namespace base {

class FakeClock : public Clock {
public:
    ~FakeClock() override {}

    Time now() override { return time_; }

    void set_time(Time t) { time_ = t; }

    void set_utc_datetime(int year, int month, int day, int hour, int min, int sec);

private:
    Time time_;
};

} // namespace base

#endif // BASE_TIME_FAKE_CLOCK_H_
