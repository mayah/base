#include "base/file/path.h"

namespace file {

namespace internal {

std::string join_path_impl(std::initializer_list<strings::StringPiece> paths)
{
    std::string result;
    for (strings::StringPiece path : paths) {
        if (path.empty())
            continue;

        if (result.empty()) {
            result = path.as_string();
            continue;
        }

        if (result.back() == '/') {
            if (is_absolute_path(path)) {
                result += path.substr(1);
            } else {
                result += path;
            }
        } else {
            if (is_absolute_path(path)) {
                result += path;
            } else {
                result += '/';
                result += path;
            }
        }
    }

    return result;
}

std::string join_path_respect_absolute_impl(std::initializer_list<strings::StringPiece> paths)
{
    std::string result;
    for (strings::StringPiece path : paths) {
        if (path.empty())
            continue;

        if (result.empty()) {
            result = path.as_string();
            continue;
        }

        if (is_absolute_path(path)) {
            result = path.as_string();
            continue;
        }

        if (result.back() == '/') {
            result += path;
        } else {
            result += '/';
            result += path;
        }
    }

    return result;
}

} // namespace internal

bool is_absolute_path(strings::StringPiece path)
{
    return !path.empty() && path[0] == '/';
}

}
