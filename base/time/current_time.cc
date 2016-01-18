#include "base/time/current_time.h"

#include <sys/time.h>

namespace base {

double current_time()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

std::int64_t current_time_in_millis()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

} // namespace base
