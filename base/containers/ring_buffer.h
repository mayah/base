#ifndef BASE_CONTAINERS_RING_BUFFER_H_
#define BASE_CONTAINERS_RING_BUFFER_H_

#include <cstddef>
#include <memory>

#include "third_party/glog/glog/logging.h"

namespace base {

template<typename T>
class RingBuffer {
public:
    explicit RingBuffer(std::size_t capacity);
    ~RingBuffer();

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    std::size_t available() const { return capacity_ - size_; }

    void clear();

    void push_back(const T& t);
    void push_back(T&& t);
    void push_front(const T& t);
    void push_front(T&& t);

    void pop_back();
    void pop_front();

    const T& front() const;
    T& front();
    const T& back() const;
    T& back();

private:
    T* ptr() { return reinterpret_cast<T*>(data_.get()); }
    const T* ptr() const { return reinterpret_cast<const T*>(data_.get()); }

    std::unique_ptr<char[]> data_;
    const std::size_t capacity_;

    std::size_t pos_;
    std::size_t size_;
};

template<typename T>
RingBuffer<T>::RingBuffer(std::size_t capacity) :
    data_(new char[sizeof(T) * capacity]),
    capacity_(capacity),
    pos_(0),
    size_(0)
{
}

template<typename T>
RingBuffer<T>::~RingBuffer()
{
    clear();
}

template<typename T>
void RingBuffer<T>::clear()
{
    while (size() > 0) {
        pop_front();
    }
}

template<typename T>
void RingBuffer<T>::push_back(const T& v)
{
    DCHECK_LT(size(), capacity());

    std::size_t index = pos_ + size_;
    if (index >= capacity())
        index -= capacity();

    new (ptr() + index) T(v);
    ++size_;
}

template<typename T>
void RingBuffer<T>::push_back(T&& v)
{
    DCHECK_LT(size(), capacity());

    std::size_t index = pos_ + size_;
    if (index >= capacity())
        index -= capacity();

    new (ptr() + index) T(std::move(v));
    ++size_;
}

template<typename T>
void RingBuffer<T>::push_front(const T& v)
{
    DCHECK_LT(size(), capacity());

    std::size_t index = pos_ + capacity() - 1;
    if (index >= capacity())
        index -= capacity();
    new (ptr() + index) T(v);
    ++size_;
    pos_ = index;
}

template<typename T>
void RingBuffer<T>::push_front(T&& v)
{
    DCHECK_LT(size(), capacity());

    std::size_t index = pos_ + capacity() - 1;
    if (index >= capacity())
        index -= capacity();
    new (ptr() + index) T(std::move(v));
    ++size_;
    pos_ = index;
}

template<typename T>
void RingBuffer<T>::pop_back()
{
    DCHECK_GT(size(), 0U);

    std::size_t index = pos_ + size_;
    if (index >= capacity())
        index -= capacity();

    ptr()[index].~T();
    --size_;
}

template<typename T>
void RingBuffer<T>::pop_front()
{
    DCHECK_GT(size(), 0U);

    std::size_t index = pos_;
    ptr()[index].~T();
    ++pos_;
    if (pos_ >= capacity()) {
        pos_ = 0;
    }
    --size_;
}

template<typename T>
const T& RingBuffer<T>::front() const
{
    DCHECK_GT(size(), 0U);
    return ptr()[pos_];
}

template<typename T>
T& RingBuffer<T>::front()
{
    DCHECK_GT(size(), 0U);
    return ptr()[pos_];
}

template<typename T>
const T& RingBuffer<T>::back() const
{
    DCHECK_GT(size(), 0U);

    std::size_t index = pos_ + size() - 1;
    if (index >= capacity())
        index -= capacity();

    return ptr()[index];
}

template<typename T>
T& RingBuffer<T>::back()
{
    DCHECK_GT(size(), 0U);

    std::size_t index = pos_ + size() - 1;
    if (index >= capacity())
        index -= capacity();

    return ptr()[index];
}

} // namespace base

#endif // BASE_CONTAINERS_RING_BUFFER_H_
