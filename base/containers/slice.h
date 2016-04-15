#ifndef BASE_CONTAINERS_SLICE_H_
#define BASE_CONTAINERS_SLICE_H_

#include <stdexcept>
#include <vector>

#include <glog/logging.h>

namespace base {

template<typename T>
class Slice {
public:
    Slice() : ptr_(nullptr), len_(0) {}
    // Allow implicit conversion.
    Slice(const std::vector<T>& vs) : ptr_(vs.data()), len_(vs.size()) {}
    Slice(const T* ptr, size_t len) : ptr_(ptr), len_(len) {}

    typedef const T* iterator;
    typedef const T* const_iterator;

    const T* data() const { return ptr_; }
    const T& get(size_t idx) const;
    size_t size() const { return len_; }
    bool empty() const { return len_ == 0; }

    void clear()
    {
        ptr_ = nullptr;
        len_ = 0;
    }

    const T& operator[](size_t idx) { return get(idx); }

    Slice subseq(size_t pos, size_t len) const;

    iterator begin() const { return data(); }
    iterator end() const { return data() + len_; }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }

    const T& front() const { return *begin(); }
    const T& back() const { return *(begin() + len_ - 1); }

private:
    const T* ptr_;
    size_t len_;
};

template<typename T>
inline const T& Slice<T>::get(size_t idx) const
{
    DCHECK_LT(idx, size());
    return ptr_[idx];
}

template<typename T>
Slice<T> Slice<T>::subseq(size_t pos, size_t len) const
{
    if (pos > size())
        throw std::out_of_range("index out of bounds");

    if (pos + len > size())
        len = size() - pos;

    return Slice(ptr_ + pos, len);
}

} // namespace base

#endif // BASE_CONTAINERS_SLICE_H_
