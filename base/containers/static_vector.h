#ifndef BASE_CONTAINERS_STATIC_VECTOR_H_
#define BASE_CONTAINERS_STATIC_VECTOR_H_

#include <cstddef>
#include <new>

#include <glog/logging.h>

namespace base {

// StaticVector is similar to std::vector, however, it allocates data memory
// in stack.
template<typename T, std::size_t N>
class StaticVector {
public:
    StaticVector();
    ~StaticVector();

    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    std::size_t capacity() const { return N; }

    // Inserts an element at back. If size exceeded, the result is undefined.
    void push_back(const T& value);
    // Removes the last element. When the container is empty, the result is undefined.
    void pop_back();

    T* begin() { return ptr(); }
    T* end() { return ptr() + size_; }
    const T* begin() const { return ptr(); }
    const T* end() const { return ptr() + size_; }
    const T* cbegin() const { return ptr(); }
    const T* cend() const { return ptr() + size_; }

    T& operator[](int index) { return ptr()[index]; }
    const T& operator[](int index) const { return ptr()[index]; }

private:
    const T* ptr() const { return reinterpret_cast<T*>(data_); }
    T* ptr() { return reinterpret_cast<T*>(data_); }

    std::size_t size_;
    char data_[sizeof(T) * N];
};

template<typename T, std::size_t N>
StaticVector<T, N>::StaticVector() :
    size_(0)
{
}

template<typename T, std::size_t N>
StaticVector<T, N>::~StaticVector()
{
    for (std::size_t i = 0; i < size_; ++i) {
        ptr()[i].~T();
    }
}

template<typename T, std::size_t N>
void StaticVector<T, N>::push_back(const T& value)
{
    CHECK_LT(size_, N);
    new (ptr() + size_++) T(value);
}

template<typename T, std::size_t N>
void StaticVector<T, N>::pop_back()
{
    CHECK_GT(size_, 0UL);
    ptr()[size_--].~T();
}

} // namespace base

#endif // BASE_CONTAINERS_STATIC_VECTOR_H_
