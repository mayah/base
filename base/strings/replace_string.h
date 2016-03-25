#ifndef BASE_STRINGS_STRING_REPLACE_H_
#define BASE_STRINGS_STRING_REPLACE_H_

#include <string>
#include "base/strings/string_piece.h"

namespace strings {

std::string replace_string(StringPiece s, StringPiece old_sub, StringPiece new_sub, bool replace_all);

} // namespace base

#endif // BASE_STRINGS_STRING_REPLACE_H_
