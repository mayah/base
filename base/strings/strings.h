#ifndef BASE_STRINGS_STRINGS_H_
#define BASE_STRINGS_STRINGS_H_

#include <string>

#include "base/strings/string_piece.h"

namespace strings {

std::string concat(StringPiece s1, StringPiece s2);
std::string concat(StringPiece s1, StringPiece s2, StringPiece s3);

inline bool has_prefix(StringPiece s, StringPiece prefix) { return s.starts_with(prefix); }
inline bool has_suffix(StringPiece s, StringPiece suffix) { return s.ends_with(suffix); }

std::string repeat(StringPiece s, int count);

// If the length of |s| is less than |n|, add |c| to left.
std::string pad_left(StringPiece s, size_t n, char c);
std::string pad_right(StringPiece s, size_t n, char c);

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
std::string tolower_ascii(StringPiece s);
std::string toupper_ascii(StringPiece s);

} // namespace strings

#endif // BASE_STRINGS_STRINGS_H_
