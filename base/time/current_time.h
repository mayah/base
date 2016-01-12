#ifndef BASE_TIME_CURRENT_TIME_H_
#define BASE_TIME_CURRENT_TIME_H_

#include <cstdint>

namespace base {

// Returns current time in seconds.
double currentTime();

// Returns current time in milli seconds.
std::int64_t currentTimeInMillis();

} // namespace base

#endif // BASE_TIME_CURRENT_TIME_H_
