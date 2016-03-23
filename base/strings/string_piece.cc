#include "base/strings/string_piece.h"

#include <algorithm>
#include <climits>
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

StringPiece::size_type StringPiece::find(char c, StringPiece::size_type pos) const
{
    if (pos > length_)
        return npos;

    const char* result = std::find(ptr_ + pos, ptr_ + length_, c);
    const size_type xpos = result - ptr_;
    return xpos < length_ ? xpos : npos;
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

StringPiece::size_type StringPiece::rfind(char c, StringPiece::size_type pos) const
{
    if (empty())
        return StringPiece::npos;

    for (size_t i = std::min(pos, size() - 1); ; --i) {
        if (get(i) == c)
            return i;
        if (i == 0)
            break;
    }
    return StringPiece::npos;
}

StringPiece::size_type StringPiece::find_first_of(StringPiece s, StringPiece::size_type pos) const
{
    if (empty() || s.empty())
        return StringPiece::npos;

    if (s.size() == 1)
        return StringPiece::find_first_of(s[0], pos);

    bool lookup_table[UCHAR_MAX + 1] {};
    for (unsigned char c : s)
        lookup_table[c] = true;

    for (size_t i = pos; i < this->size(); ++i) {
        if (lookup_table[static_cast<unsigned char>((*this)[i])])
            return i;
    }

    return StringPiece::npos;
}

StringPiece::size_type StringPiece::find_last_of(StringPiece s, StringPiece::size_type pos) const
{
    if (empty() || s.empty())
        return StringPiece::npos;

    if (s.size() == 1)
        return StringPiece::find_last_of(s[0], pos);

    bool lookup_table[UCHAR_MAX + 1] {};
    for (unsigned char c : s)
        lookup_table[c] = true;
    for (size_t i = std::min(pos, size() - 1); ; --i) {
        if (lookup_table[static_cast<unsigned char>(get(i))])
            return i;
        if (i == 0)
            break;
    }
    return StringPiece::npos;
}

StringPiece::size_type StringPiece::find_first_not_of(char c, StringPiece::size_type pos) const
{
    if (empty())
        return StringPiece::npos;

    for (size_t i = pos; i < this->size(); ++i) {
        if (get(i) != c)
            return i;
    }

    return StringPiece::npos;
}

StringPiece::size_type StringPiece::find_last_not_of(char c, StringPiece::size_type pos) const
{
    if (empty())
        return StringPiece::npos;

    for (size_t i = std::min(pos, size() - 1); ; --i) {
        if (get(i) != c)
            return i;
        if (i == 0)
            break;
    }

    return StringPiece::npos;
}

StringPiece::size_type StringPiece::find_first_not_of(StringPiece s, StringPiece::size_type pos) const
{
    if (empty())
        return StringPiece::npos;
    if (s.size() == 0)
        return 0U;
    if (s.size() == 1)
        return StringPiece::find_first_not_of(s[0], pos);

    bool lookup_table[UCHAR_MAX + 1] {};
    for (unsigned char c : s)
        lookup_table[c] = true;

    for (size_t i = pos; i < this->size(); ++i) {
        if (!lookup_table[static_cast<unsigned char>(get(i))])
            return i;
    }

    return StringPiece::npos;
}

StringPiece::size_type StringPiece::find_last_not_of(StringPiece s, StringPiece::size_type pos) const
{
    if (empty())
        return StringPiece::npos;
    if (s.size() == 0)
        return size() - 1;
    if (s.size() == 1)
        return StringPiece::find_last_not_of(s[0], pos);

    bool lookup_table[UCHAR_MAX + 1] {};
    for (unsigned char c : s)
        lookup_table[c] = true;

    for (size_t i = std::min(pos, size() - 1); ; --i) {
        if (!lookup_table[static_cast<unsigned char>(get(i))])
            return i;
        if (i == 0)
            break;
    }

    return StringPiece::npos;
}

StringPiece StringPiece::chomp() const
{
    if (empty())
        return StringPiece();

    if (size() == 1) {
        if (back() == '\r' || back() == '\n')
            return StringPiece();
        return *this;
    }

    if (back() == '\r')
        return substr(0, size() - 1);
    if (back() == '\n') {
        if (get(size() - 2) == '\r')
            return StringPiece(data(), size() - 2);
        return StringPiece(data(), size() - 1);
    }

    return *this;
}

StringPiece StringPiece::substr(size_t pos, size_t n) const
{
    if (pos > size())
        pos = size();
    if (n > size() - pos)
        n = size() - pos;
    return StringPiece(data() + pos, n);
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
