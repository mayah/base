#include "base/strings/string_piece.h"

#include <algorithm>
#include <cstring>

namespace strings {

const StringPiece::size_type StringPiece::npos = StringPiece::size_type(-1);

StringPiece::size_type StringPiece::find(StringPiece s, StringPiece::size_type pos) const
{
    if (pos > length_)
        return npos;

    const char* result = std::search(ptr_ + pos, ptr_ + length_, s.ptr_, s.ptr_ + s.length_);
    const size_type xpos = result - ptr_;
    return xpos + s.length_ <= length_ ? xpos : npos;
}

StringPiece::size_type StringPiece::rfind(StringPiece s, StringPiece::size_type pos) const
{
    if (length_ < s.length_)
        return npos;

    if (s.length_ == 0)
        return std::min(length_, pos);

    const char* last = ptr_ + std::min(length_ - s.length_, pos) + s.length_;
    const char* result = std::find_end(ptr_, last, s.ptr_, s.ptr_ + s.length_);
    return result != last ? result - ptr_ : npos;
}

std::ostream& operator<<(std::ostream& os, StringPiece s)
{
    os.write(s.data(), static_cast<std::streamsize>(s.size()));
    return os;
}

bool operator==(StringPiece lhs, StringPiece rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    if (lhs.data() == rhs.data() || lhs.size() <= 0)
        return true;

    size_t len = lhs.size();
    return memcmp(lhs.data(), rhs.data(), len) == 0;
}


bool operator<(StringPiece lhs, StringPiece rhs)
{
    const int r = std::memcmp(lhs.data(), rhs.data(), std::min(lhs.size(), rhs.size()));
    return r < 0 || (r == 0 && lhs.size() < rhs.size());
}

} // namespace strings
