#include "base/time/time.h"

#include <string.h>
#include <time.h>

namespace base {

std::string Time::to_localtime_string() const
{
    char buf[80];
    time_t t = to_time_t();
    ctime_r(&t, buf);

    // Drop the last \n from buf.
    size_t len = strlen(buf);
    if (len == 0)
        return std::string();

    return std::string(buf, buf + (len - 1));
}

bool Time::to_tm(std::tm* stm) const
{
    time_t tt = to_time_t();
    return gmtime_r(&tt, stm) != nullptr;
}

}
