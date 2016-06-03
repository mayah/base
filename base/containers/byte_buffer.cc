#include "base/containers/byte_buffer.h"

namespace base {

ByteBuffer::ByteBuffer()
{
}

ByteBuffer::ByteBuffer(size_t capacity)
{
    buf_.reserve(capacity);
}

ByteBuffer::~ByteBuffer()
{
}

} // namespace base
