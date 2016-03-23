#ifndef BASE_STRINGS_JOIN_H_
#define BASE_STRINGS_JOIN_H_

#include <string>
#include <vector>

#include "base/strings/string_piece.h"

namespace strings {

std::string join(const std::vector<std::string>& parts, StringPiece sep);

} // namesapce strings

#endif // BASE_STRINGS_JOIN_H_
