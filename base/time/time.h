#ifndef BASE_TIME_TIME_H_
#define BASE_TIME_TIME_H_

#include <chrono>
#include <ostream>

namespace base {

class Time {
public:
    Time() {}
    explicit Time(std::chrono::system_clock::time_point tp) : tp_(tp) {}

    const std::chrono::system_clock::time_point& time_point() const { return tp_; }
    time_t to_time_t() const { return std::chrono::system_clock::to_time_t(tp_); }

    std::string to_localtime_string() const;

private:
    std::chrono::system_clock::time_point tp_;
};

} // namespace base

#endif // BASE_TIME_TIME_H_
