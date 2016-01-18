#ifndef BASE_TIME_TIME_H_
#define BASE_TIME_TIME_H_

#include <chrono>

namespace base {

class Time {
public:
    Time() {}
    explicit Time(std::chrono::system_clock::time_point tp) : tp_(tp) {}

    const std::chrono::system_clock::time_point& timePoint() const { return tp_; }
    time_t toTimeT() const { return std::chrono::system_clock::to_time_t(tp_); }

private:
    std::chrono::system_clock::time_point tp_;
};

} // namespace base

#endif // BASE_TIME_TIME_H_
