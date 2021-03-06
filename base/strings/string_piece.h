#ifndef BASE_STRINGS_STRING_PIECE_H_
#define BASE_STRINGS_STRING_PIECE_H_

#include <cstddef>
#include <ostream>
#include <string>

#include "third_party/glog/glog/logging.h"

namespace strings {

class StringPiece {
public:
    StringPiece() : ptr_(nullptr), length_(0) {}
    StringPiece(const std::string& s) : ptr_(s.data()), length_(s.size()) {}
    StringPiece(const char* s, size_t len) : ptr_(s), length_(len) {}
    StringPiece(const char* s) : ptr_(s), length_(s ? strlen(s) : 0) {}

    typedef size_t size_type;
    typedef char value_type;
    typedef const value_type* pointer;
    typedef const value_type& reference;
    typedef const value_type& const_reference;
    typedef std::ptrdiff_t difference_type;
    typedef const value_type* iterator;
    typedef const value_type* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    static const size_type npos;

    const char* data() const { return ptr_; }
    size_type size() const { return length_; }
    size_type length() const { return length_; }
    bool empty() const { return length_ == 0; }

    void clear()
    {
        ptr_ = nullptr;
        length_ = 0;
    }

    std::string as_string() const
    {
        if (!ptr_)
            return std::string();
        return std::string(data(), size());
    }

    bool starts_with(StringPiece x) const
    {
        if (size() < x.size())
            return false;
        return memcmp(data(), x.data(), x.length()) == 0;
    }

    bool ends_with(StringPiece x) const
    {
        if (size() < x.size())
            return false;
        return memcmp(data() + size() - x.size(), x.data(), x.size()) == 0;
    }

    char get(size_t i) const
    {
        DCHECK_LE(0U, i);
        DCHECK_LT(i, length_);
        return ptr_[i];
    }
    char operator[](size_t i) const { return get(i); }

    // Returns the string whose last LF, CR, or CRLF is removed.
    StringPiece chomp() const;

    StringPiece substr(size_t pos, size_t n = npos) const;

    char front() const { return *ptr_; }
    char back() const { return *(ptr_ + length_ - 1); }

    iterator begin() const { return data(); }
    iterator end() const { return data() + size(); }
    const_iterator cbegin() const { return data(); }
    const_iterator cend() const { return end(); }

    size_type find(StringPiece s, size_type pos = 0) const;
    size_type find(char c, size_type pos = 0) const;
    size_type rfind(StringPiece s, size_type pos = npos) const;
    size_type rfind(char c, size_type pos = npos) const;

    size_type find_first_of(char c, size_type pos = 0) const { return find(c, pos); }
    size_type find_first_of(StringPiece s, size_type pos = 0) const;
    size_type find_first_not_of(char c, size_type pos = 0) const;
    size_type find_first_not_of(StringPiece s, size_type pos = 0) const;

    size_type find_last_of(char c, size_type pos = npos) const { return rfind(c, pos); }
    size_type find_last_of(StringPiece s, size_type pos = npos) const;
    size_type find_last_not_of(char c, size_type pos = npos) const;
    size_type find_last_not_of(StringPiece s, size_type pos = npos) const;

private:
    const value_type* ptr_;
    size_type length_;
};

bool operator==(StringPiece lhs, StringPiece rhs);
bool operator<(StringPiece lhs, StringPiece rhs);

inline bool operator!=(StringPiece lhs, StringPiece rhs) { return !(lhs == rhs); }
inline bool operator>(StringPiece lhs, StringPiece rhs) { return rhs < lhs; }
inline bool operator<=(StringPiece lhs, StringPiece rhs) { return !(lhs > rhs); }
inline bool operator>=(StringPiece lhs, StringPiece rhs) { return !(lhs < rhs); }

std::ostream& operator<<(std::ostream&, StringPiece);

// |str| and |sp| should not be overlaped.
inline std::string& operator+=(std::string& str, StringPiece sp) { return str.append(sp.data(), sp.size()); }

} // namespace strings

#endif // BASE_STRINGS_STRING_PIECE_H_
