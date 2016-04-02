#ifndef BASE_STRINGS_ASCII_CTYPE_H_
#define BASE_STRINGS_ASCII_CTYPE_H_

// Since these functions in libc will check locale, it could be slow and unpredictable.
// So we implement them.

namespace strings {

inline char isspace_ascii(char c)
{
    switch (c) {
    case ' ':
    case '\r':
    case '\n':
    case '\t':
    case '\v':
    case '\f':
        return true;
    default:
        return false;
    }
}

} // namespace strings

#endif // BASE_STRINGS_ASCII_CTYPE_H_
