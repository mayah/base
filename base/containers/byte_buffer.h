#ifndef BASE_CONTAINERS_BYTE_BUFFER_H_
#define BASE_CONTAINERS_BYTE_BUFFER_H_

#include <cstddef>
#include <vector>

namespace base {

// ByteBuffer is an extensible byte array.
// This is almost the same as std::vector<char>,
// but more understandable name.
class ByteBuffer {
public:
    ByteBuffer();
    explicit ByteBuffer(size_t capacity);
    ~ByteBuffer();

    size_t capacity() const { return buf_.capacity(); }
    size_t size() const { return buf_.size(); }
    void reserve(size_t size) { return buf_.reserve(size); }

    void* data() { return buf_.data(); }
    const void* data() const { return buf_.data(); }

    char& operator[](size_t index) { return buf_[index]; }
    const char& operator[](size_t index) const { return buf_[index]; }

    void push_back(char c) { buf_.push_back(c); }

private:
    std::vector<char> buf_;
};

} // namespace base

#endif // BASE_CONTAINERS_BYTE_BUFFER_H_
