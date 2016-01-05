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

bool isAbsolutePath(strings::StringPiece path);

template<typename... T>
std::string joinPath(const T&... args)
{
    return internal::joinPathImpl({args...});
}

template<typename... T>
std::string joinPathRespectAbsolute(const T&... args)
{
    return internal::joinPathRespectAbsoluteImpl({args...});
}

} // namespace file

#endif // BASE_FILE_PATH_H_
