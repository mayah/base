#ifndef BASE_TIME_CLOCK_H_
#define BASE_TIME_CLOCK_H_

#include "base/time/time.h"

namespace base {

class Clock {
public:
    // Returns a pointer to real clock.
    static Clock* real_clock();

    virtual ~Clock() {}

    // Returns current time.
    virtual Time now() = 0;
};

} // namespace base

#endif // BASE_TIME_CLOCK_H_
