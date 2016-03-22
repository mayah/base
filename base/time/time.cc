#include "base/time/time.h"

namespace base {

std::string Time::to_localtime_string() const
{
    char buf[80];
    time_t t = to_time_t();
    ctime_r(&t, buf);

    return buf;
}

}
