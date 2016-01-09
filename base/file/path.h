#ifndef BASE_FILE_PATH_H_
#define BASE_FILE_PATH_H_

#include <initializer_list>
#include <string>

#include "base/strings/string_piece.h"

namespace file {

namespace internal {
std::string joinPathImpl(std::initializer_list<strings::StringPiece> paths);
std::string joinPathRespectAbsoluteImpl(std::initializer_list<strings::StringPiece> paths);
} // namespace internal

// Returns true if |path| is absolute.
bool isAbsolutePath(strings::StringPiece path);

// Joins path.
// For example:
//   1.  /A/, /B/C --> /A/B/C
//   2.  A/B, B/C/ --> A/B/B/C/
//   3.  /, /A/B, /C --> /A/B/C
template<typename... T>
std::string joinPath(const T&... args)
{
    return internal::joinPathImpl({args...});
}

// Joins path. If some path is absolute, we respect it.
// For example:
//   1.  /A, /B/C --> /B/C    (/B/C is absolute)
//   2.  /A, B/C --> /A/B/C
//   3.  A, B/C --> A/B/C
//   4.  A, /B/C --> /B/C     (/B/C is absolute, it's respected.
template<typename... T>
std::string joinPathRespectAbsolute(const T&... args)
{
    return internal::joinPathRespectAbsoluteImpl({args...});
}

} // namespace file

#endif // BASE_FILE_PATH_H_
