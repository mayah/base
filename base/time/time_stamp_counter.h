#ifndef BASE_TIME_TIME_STAMP_COUNTER_H_
#define BASE_TIME_TIME_STAMP_COUNTER_H_

#include <vector>

namespace base {

// Unfortunately, __rdtscp is not defined in /usr/lib/gcc/x86_64-linux-gnu/4.4/include/x86intrin.
inline unsigned long long rdtscp(unsigned int* aux)
{
    unsigned long long rax, rdx;
    asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
    return (rdx << 32) + rax;
}

class TimeStampCounterData {
public:
    void add(unsigned long long t) { data_.push_back(t); }

    void showStatistics() const;

private:
    std::vector<unsigned long long> data_;
};

// Precision of this timer depends on the CPU clock of the machine running on.
// Use rdtscp instead of rdtsc. rdtsc allows out-of-order execution, so time is not accurate.
class ScopedTimeStampCounter {
public:
    // Don't take the ownership of tsc
    explicit ScopedTimeStampCounter(TimeStampCounterData* tsc) :
        tsc_(tsc),
        start_(rdtscp(&a_))
    {
    }

    ~ScopedTimeStampCounter()
    {
        unsigned long long end = rdtscp(&a_);
        if (end > start_)
            tsc_->add(end - start_);
    }

private:
    TimeStampCounterData* tsc_;
    unsigned int a_;
    unsigned long long start_;
};

} // namespace base

#endif // BASE_TIME_TIME_STAMP_COUNTER_H_

