#ifndef BASE_STRINGS_JOIN_H_
#define BASE_STRINGS_JOIN_H_

#include <string>
#include <vector>

#include "base/strings/string_piece.h"

namespace strings {

template<typename Iterator>
std::string join(Iterator begin, Iterator end, StringPiece sep)
{
    bool first = true;
    std::string s;
    for (Iterator it = begin; it != end; ++it) {
        if (first) {
            first = false;
        } else {
            s += sep;
        }

        s += *it;
    }

    return s;
}

inline std::string join(const std::vector<std::string>& parts, StringPiece sep)
{
    return join(parts.begin(), parts.end(), sep);
}

} // namesapce strings

#endif // BASE_STRINGS_JOIN_H_
