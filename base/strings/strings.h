#ifndef BASE_STRINGS_STRINGS_H_
#define BASE_STRINGS_STRINGS_H_

#include <string>

#include "base/strings/string_piece.h"

namespace strings {

std::string concat(StringPiece s1, StringPiece s2);
std::string concat(StringPiece s1, StringPiece s2, StringPiece s3);

std::string join(const std::vector<std::string>& parts, StringPiece sep);

bool hasPrefix(StringPiece s, StringPiece prefix) { return s.startsWith(prefix); }
bool hasSuffix(StringPiece s, StringPiece suffix) { return s.endsWith(suffix); }

std::string repeat(StringPiece s, int count);

StringPiece trimLeft(StringPiece s, char c);
StringPiece trimLeft(StringPiece s, StringPiece cutset);
StringPiece trimRight(StringPiece s, char c);
StringPiece trimRight(StringPiece s, StringPiece cutset);

StringPiece trimSpace(StringPiece);
// If |s| starts with |prefix|, trim it.
StringPiece trimPrefix(StringPiece s, StringPiece prefix);
// If |s| ends with |suffix|, trim it.
StringPiece trimSuffix(StringPiece s, StringPiece suffix);

// Returns a new copy of |s| with removing |cut|.
std::string remove(StringPiece s, char cut);

} // namespace strings

#endif // BASE_STRINGS_STRINGS_H_
