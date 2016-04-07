#ifndef BASE_STRINGS_STRING_REPLACE_H_
#define BASE_STRINGS_STRING_REPLACE_H_

#include <string>
#include "base/strings/string_piece.h"

namespace strings {

enum class OneOrAll { ONE, ALL };
std::string replace_string(StringPiece s, StringPiece old_sub, StringPiece new_sub, OneOrAll one_or_all);

} // namespace base

#endif // BASE_STRINGS_STRING_REPLACE_H_
