#ifndef BASE_STRINGS_SPLIT_H_
#define BASE_STRINGS_SPLIT_H_

#include <string>
#include <vector>
#include "base/strings/string_piece.h"

namespace strings {

struct AllowEmpty {
    bool operator()(StringPiece sp) const { return true; }
};
struct SkipEmpty {
    bool operator()(StringPiece sp) const { return !sp.empty(); }
};

std::vector<std::string> split(StringPiece str, StringPiece seps, AllowEmpty);
std::vector<std::string> split(StringPiece str, StringPiece seps, SkipEmpty);

} // namespace strings

#endif // BASE_STRINGS_SPLIT_H_
