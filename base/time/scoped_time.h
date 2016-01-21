#ifndef BASE_TIME_SCOPED_TIME_H_
#define BASE_TIME_SCOPED_TIME_H_

#include "base/time/current_time.h"

namespace base {

class ScopedTime {
public:
    explicit ScopedTime(double* sec);
    ~ScopedTime();

private:
    double begin_;
    double* sec_;
};

inline ScopedTime::ScopedTime(double* sec) :
    begin_(current_time()),
    sec_(sec)
{
}

inline ScopedTime::~ScopedTime()
{
    *sec_ = current_time() - begin_;
}

} // namespace base

#endif // BASE_TIME_SCOPED_TIME_H_
