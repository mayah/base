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

class IntegerStepIterator {
public:
    IntegerStepIterator(int v, int step) : v_(v), step_(step) {}

    IntegerStepIterator& operator++() { v_ += step_; return *this; }
    IntegerStepIterator operator++(int) { return IntegerStepIterator(v_+ step_, step_); }

    int operator*() const { return v_; }
    friend bool operator==(const IntegerStepIterator& lhs, const IntegerStepIterator& rhs) { return lhs.v_ == rhs.v_; }
    friend bool operator!=(const IntegerStepIterator& lhs, const IntegerStepIterator& rhs) { return !(lhs == rhs); }

private:
    int v_;
    const int step_;
};

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

class XRangeStep {
public:
    XRangeStep(int begin, int end, int step) :
        begin_(begin),
        end_(begin + (end - begin + step - 1) / step * step),
        step_(step)
    {
        DCHECK_LE(begin, end);
    }

    typedef internal::IntegerStepIterator Iterator;

    Iterator begin() const { return Iterator(begin_, step_); }
    Iterator end() const { return Iterator(end_, step_); }

private:
    int begin_;
    int end_;
    int step_;
};

} // namespace internal

internal::XRange xrange(int begin, int end) { return internal::XRange(begin, end); }
internal::XRangeStep xrange(int begin, int end, int step) { return internal::XRangeStep(begin, end, step); }

} // namespace base

#endif // BASE_CONTAINERS_XRANGE_H_
