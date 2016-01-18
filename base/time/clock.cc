#include "base/time/clock.h"

namespace base {

class RealClock : public Clock {
public:
    ~RealClock() override {}

    Time now() override { return Time(std::chrono::system_clock::now()); }
};

// static
Clock* Clock::realClock()
{
    static RealClock instance;
    return &instance;
}

} // namespace base
