#ifndef BASE_FILE_PATH_H_
#define BASE_FILE_PATH_H_

// path.h contains utility methods to manipulate paths or tree traversal.

#include <initializer_list>
#include <string>

#include "base/strings/string_piece.h"

namespace file {

namespace internal {
std::string join_path_impl(std::initializer_list<strings::StringPiece> paths);
std::string join_path_respect_absolute_impl(std::initializer_list<strings::StringPiece> paths);
} // namespace internal

strings::StringPiece basename(strings::StringPiece path);
strings::StringPiece dirname(strings::StringPiece path);
strings::StringPiece stem(strings::StringPiece path);
strings::StringPiece extension(strings::StringPiece path);

// Gets current directory name. If failed, empty.
std::string get_current_directory();

// Returns true if |path| is absolute.
bool is_absolute_path(strings::StringPiece path);

// Joins path.
// For example:
//   1.  /A/, /B/C --> /A/B/C
//   2.  A/B, B/C/ --> A/B/B/C/
//   3.  /, /A/B, /C --> /A/B/C
template<typename... T>
std::string join_path(const T&... args)
{
    return internal::join_path_impl({args...});
}

// Joins path. If some path is absolute, we respect it.
// For example:
//   1.  /A, /B/C --> /B/C    (/B/C is absolute)
//   2.  /A, B/C --> /A/B/C
//   3.  A, B/C --> A/B/C
//   4.  A, /B/C --> /B/C     (/B/C is absolute, it's respected.
template<typename... T>
std::string join_path_respect_absolute(const T&... args)
{
    return internal::join_path_respect_absolute_impl({args...});
}

bool is_directory(const char* path);

bool list_files(const char* directory_path, std::vector<std::string>* files);

// Removes all files under |path|. |path| is also removed.
bool delete_tree(const char* path);

} // namespace file

#endif // BASE_FILE_PATH_H_
