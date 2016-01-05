#include "base/file/path.h"

namespace file {

namespace internal {

std::string joinPathImpl(std::initializer_list<strings::StringPiece> paths)
{
    std::string result;
    for (strings::StringPiece path : paths) {
        if (path.empty())
            continue;

        if (result.empty()) {
            result = path.asString();
            continue;
        }

        if (result.back() == '/') {
            if (isAbsolutePath(path)) {
                result += path.substr(1);
            } else {
                result += path;
            }
        } else {
            if (isAbsolutePath(path)) {
                result += path;
            } else {
                result += '/';
                result += path;
            }
        }
    }

    return result;
}

std::string joinPathRespectAbsoluteImpl(std::initializer_list<strings::StringPiece> paths)
{
    std::string result;
    for (strings::StringPiece path : paths) {
        if (path.empty())
            continue;

        if (result.empty()) {
            result = path.asString();
            continue;
        }

        if (isAbsolutePath(path)) {
            result = path.asString();
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

bool isAbsolutePath(strings::StringPiece path)
{
    return !path.empty() && path[0] == '/';
}

}
