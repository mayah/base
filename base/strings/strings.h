#ifndef BASE_STRINGS_STRINGS_H_
#define BASE_STRINGS_STRINGS_H_

#include <string>

#include "base/strings/string_piece.h"

namespace strings {

std::string concat(StringPiece s1, StringPiece s2);
std::string concat(StringPiece s1, StringPiece s2, StringPiece s3);

std::string join(const std::vector<std::string>& parts, StringPiece sep);

inline bool has_prefix(StringPiece s, StringPiece prefix) { return s.starts_with(prefix); }
inline bool has_suffix(StringPiece s, StringPiece suffix) { return s.ends_with(suffix); }

std::string repeat(StringPiece s, int count);

StringPiece trim_left(StringPiece s, char c);
StringPiece trim_left(StringPiece s, StringPiece cutset);
StringPiece trim_right(StringPiece s, char c);
StringPiece trim_right(StringPiece s, StringPiece cutset);

StringPiece trim_space(StringPiece);
// If |s| starts with |prefix|, trim it.
StringPiece trim_prefix(StringPiece s, StringPiece prefix);
// If |s| ends with |suffix|, trim it.
StringPiece trim_suffix(StringPiece s, StringPiece suffix);

// Returns a new copy of |s| with removing |cut|.
std::string remove(StringPiece s, char cut);

// Converts ASCII equivalent lower case.
char to_lower_ASCII(char c);
std::string to_lower_ASCII(StringPiece s);

char to_upper_ASCII(char c);
std::string to_upper_ASCII(StringPiece s);

} // namespace strings

#endif // BASE_STRINGS_STRINGS_H_
