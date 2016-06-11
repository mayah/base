#include "base/time/fake_clock.h"

#include <ctime>

namespace base {

void FakeClock::set_utc_datetime(int year, int month, int mday, int hour, int min, int sec)
{
    struct tm t{};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = mday;
    t.tm_hour = hour;
    t.tm_min = min;
    t.tm_sec = sec;

    time_t tt = timegm(&t);
    set_time(Time(std::chrono::system_clock::from_time_t(tt)));
}

} // namespace base
