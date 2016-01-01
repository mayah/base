#ifndef BASE_STRINGS_STRINGS_H_
#define BASE_STRINGS_STRINGS_H_

#include <string>

#include "base/strings/string_piece.h"

namespace strings {

bool hasPrefix(StringPiece s, StringPiece prefix) { return s.startsWith(prefix); }
bool hasSuffix(StringPiece s, StringPiece suffix) { return s.endsWith(suffix); }

std::string repeat(StringPiece s, int count);

StringPiece trimSpace(StringPiece);

} // namespace strings

#endif // BASE_STRINGS_STRINGS_H_
