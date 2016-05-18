#ifndef BASE_CONTAINERS_XRANGE_H_
#define BASE_CONTAINERS_XRANGE_H_

#include "third_party/glog/glog/logging.h"

namespace base {

namespace internal {
class IntegerIterator {
public:
    explicit IntegerIterator(int v) : v_(v) {}

    IntegerIterator& operator++() { ++v_; return *this; }
    IntegerIterator operator++(int) { return IntegerIterator(v_++); }

    int operator*() const { return v_; }
    friend bool operator==(IntegerIterator lhs, IntegerIterator rhs) { return lhs.v_ == rhs.v_; }
    friend bool operator!=(IntegerIterator lhs, IntegerIterator rhs) { return !(lhs == rhs); }

private:
    int v_;
};
} // namespace internal

class XRange {
public:
    XRange(int begin, int end) :
        begin_(begin),
        end_(end)
    {
        DCHECK_LE(begin, end);
    }

    typedef internal::IntegerIterator Iterator;

    Iterator begin() const { return Iterator(begin_); }
    Iterator end() const { return Iterator(end_); }

private:
    int begin_;
    int end_;
};

XRange xrange(int begin, int end) { return XRange(begin, end); }

} // namespace base

#endif // BASE_CONTAINERS_XRANGE_H_
