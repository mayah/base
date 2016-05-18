#ifndef BASE_CONTAINERS_FLAG_SET_H_
#define BASE_CONTAINERS_FLAG_SET_H_

#include <cstdint>

#include "third_party/glog/glog/logging.h"

namespace base {

// FlagSet is an integer set that contains [0, 64).
class FlagSet {
public:
    void set(int x)
    {
        DCHECK(0 <= x && x < 64) << x;
        v_ |= (1ULL << x);
    }

    void unset(int x)
    {
        DCHECK(0 <= x && x < 64) << x;
        v_ &= ~(1ULL << x);
    }

    bool is_set(int x) const
    {
        DCHECK(0 <= x && x < 64) << x;
        return v_ & (1ULL << x);
    }

    bool empty() const { return v_ == 0; }
    int size() const { return __builtin_popcountll(v_); }

    int smallest() const
    {
        DCHECK(!empty());
        return __builtin_ctzll(v_);
    }

    void remove_smallest()
    {
        v_ = v_ & (v_ - 1);
    }

    friend bool operator==(FlagSet lhs, FlagSet rhs) { return lhs.v_ == rhs.v_; }
    friend bool operator!=(FlagSet lhs, FlagSet rhs) { return lhs.v_ != rhs.v_; }

private:
    std::uint64_t v_ = 0;
};

} // namespace base

#endif // BASE_CONTAINERS_FLAG_SET_H_
