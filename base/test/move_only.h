#ifndef BASE_TEST_MOVE_ONLY_H_
#define BASE_TEST_MOVE_ONLY_H_

// MoveOnlyInt is just int, but does not have copy constructor.
// This is for testing purpose only.

#include "base/macros.h"

namespace base {

class MoveOnlyInt {
public:
    explicit MoveOnlyInt(int v) : v_(v) {}
    MoveOnlyInt(MoveOnlyInt&& moi) noexcept : v_(moi.v_) {}

    MoveOnlyInt& operator=(MoveOnlyInt&& oi) noexcept {
        v_ = oi.v_;
        return *this;
    }

    int get() const { return v_; }

private:
    int v_;

    DISALLOW_COPY_AND_ASSIGN(MoveOnlyInt);
};

} // namespace base

#endif // BASE_TEST_MOVE_ONLY_H_
