#ifndef BASE_FILE_PATH_H_
#define BASE_FILE_PATH_H_

#include <initializer_list>
#include <string>

#include "base/strings/string_piece.h"

namespace file {

bool isAbsolutePath(strings::StringPiece path);

std::string joinPathImpl(std::initializer_list<strings::StringPiece> paths);

template<typename... T>
std::string joinPath(const T&... args)
{
    return joinPathImpl({args...});
}

} // namespace file

#endif // BASE_FILE_PATH_H_
