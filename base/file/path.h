#ifndef BASE_FILE_PATH_H_
#define BASE_FILE_PATH_H_

#include "base/strings/string_piece.h"

namespace file {

bool isAbsolutePath(strings::StringPiece path);

} // namespace file

#endif // BASE_FILE_PATH_H_
