#ifndef BASE_TIME_LAP_TIMER_H_
#define BASE_TIME_LAP_TIMER_H_

#include <string>
#include <vector>

#include "base/time/clock.h"
#include "base/time/time.h"

namespace base {

// LapTimer remembers the time and message, and show them.
class LapTimer {
public:
    LapTimer();

    // Takes the current time with message.
    void lap(std::string message);

    const std::vector<std::pair<base::Time, std::string>>& laps() const { return laps_; }

private:
    Clock* clock_;
    std::vector<std::pair<base::Time, std::string>> laps_;
};

} // namespace base

#endif // BASE_TIME_LAP_TIMER_H_
