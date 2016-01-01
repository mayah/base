#ifndef BASE_CONTAINERS_SMALL_INT_SET_H_
#define BASE_CONTAINERS_SMALL_INT_SET_H_

#include <cstdint>
#include <glog/logging.h>

// SmallIntSet is an integer set that contains [0, 64).
class SmallIntSet {
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

    bool isSet(int x) const
    {
        DCHECK(0 <= x && x < 64) << x;
        return v_ & (1ULL << x);
    }

    bool isEmpty() const { return v_ == 0; }
    int size() const { return __builtin_popcountll(v_); }

    int smallest() const
    {
        DCHECK(!isEmpty());
        return __builtin_ctzll(v_);
    }

    void removeSmallest()
    {
        v_ = v_ & (v_ - 1);
    }

    friend bool operator==(SmallIntSet lhs, SmallIntSet rhs) { return lhs.v_ == rhs.v_; }
    friend bool operator!=(SmallIntSet lhs, SmallIntSet rhs) { return lhs.v_ != rhs.v_; }

private:
    std::uint64_t v_ = 0;
};

#endif // BASE_CONTAINERS_SMALL_INT_SET_H_
