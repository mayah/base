#ifndef BASE_TIME_CURRENT_TIME_H_
#define BASE_TIME_CURRENT_TIME_H_

#include <cstdint>

namespace base {

// Returns current time in seconds.
double current_time();

// Returns current time in milli seconds.
std::int64_t current_time_in_millis();

} // namespace base

#endif // BASE_TIME_CURRENT_TIME_H_
