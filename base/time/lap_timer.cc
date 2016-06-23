#include "base/time/lap_timer.h"

#include <iostream>

namespace base {

LapTimer::LapTimer() :
    clock_(Clock::real_clock())
{
}

void LapTimer::lap(std::string message)
{
    laps_.emplace_back(clock_->now(), std::move(message));
}

} // namespace base
