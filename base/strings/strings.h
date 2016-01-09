#ifndef BASE_STRINGS_STRINGS_H_
#define BASE_STRINGS_STRINGS_H_

#include <string>

#include "base/strings/string_piece.h"

namespace strings {

std::string concat(StringPiece s1, StringPiece s2);
std::string concat(StringPiece s1, StringPiece s2, StringPiece s3);

bool hasPrefix(StringPiece s, StringPiece prefix) { return s.startsWith(prefix); }
bool hasSuffix(StringPiece s, StringPiece suffix) { return s.endsWith(suffix); }

std::string repeat(StringPiece s, int count);

StringPiece trimSpace(StringPiece);
// If |s| starts with |prefix|, trim it.
StringPiece trimPrefix(StringPiece s, StringPiece prefix);
// If |s| ends with |suffix|, trim it.
StringPiece trimSuffix(StringPiece s, StringPiece suffix);

} // namespace strings

#endif // BASE_STRINGS_STRINGS_H_
