#include "base/file/path.h"

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "base/strings/strings.h"

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

// This is not the same as posix dirname.
// ours always return substr of the path.
//
// path        POSIX                 OURS
//             dirname   basename    dirname   basename
// -----------------------------------------------------------
// /usr/lib    /usr      lib         /usr      lib
// /usr/       /         usr         /         usr
// usr         .         usr         <empty>   usr
// /           /         /           /         <empty>
// .           .         .           <empty>   .
// ..          .         ..          <empty>   ..

strings::StringPiece basename(strings::StringPiece path)
{
    path = strings::trim_right(path, '/');
    if (path.empty())
        return strings::StringPiece();

    strings::StringPiece::size_type pos = path.find_last_of('/');
    if (pos == strings::StringPiece::npos)
        return path;
    return path.substr(pos + 1);
}

strings::StringPiece dirname(strings::StringPiece path)
{
    if (path == "/")
        return path;

    path = strings::trim_right(path, '/');
    if (path.empty())
        return strings::StringPiece();

    strings::StringPiece::size_type pos = path.find_last_of('/');
    if (pos == strings::StringPiece::npos)
        return path.substr(0, 0);
    if (pos == 0)
        return path.substr(0, 1);
    return path.substr(0, pos);
}

strings::StringPiece stem(strings::StringPiece path)
{
    path = basename(path);
    strings::StringPiece::size_type pos = path.find_last_of('.');
    if (pos == strings::StringPiece::npos)
        return path;
    return path.substr(0, pos);
}

strings::StringPiece extension(strings::StringPiece path)
{
    path = basename(path);
    strings::StringPiece::size_type pos = path.find_last_of('.');
    if (pos == strings::StringPiece::npos)
        return strings::StringPiece();
    return path.substr(pos);
}

bool is_absolute_path(strings::StringPiece path)
{
    return !path.empty() && path[0] == '/';
}

bool is_directory(const char* path)
{
    struct stat st;
    if (stat(path, &st) < 0)
        return false;

    return S_ISDIR(st.st_mode);
}

bool list_files(const char* directory_path, std::vector<std::string>* files)
{
    DIR* dir = opendir(directory_path);
    if (!dir)
        return false;

    while (true) {
        struct dirent* dent = readdir(dir);
        if (!dent)
            break;
        files->push_back(dent->d_name);
    }

    if (closedir(dir) < 0)
        return false;

    return true;
}

bool delete_tree(const char* path)
{
    struct stat st;
    if (stat(path, &st) < 0) {
        return false;
    }

    if (!S_ISDIR(st.st_mode)) {
        if (unlink(path) < 0) {
            return false;
        }
        return true;
    }

    std::vector<std::string> files;
    if (!list_files(path, &files)) {
        return false;
    }

    for (const auto& file : files) {
        if (file == "." || file == "..")
            continue;

        std::string p = join_path(path, file);
        if (!delete_tree(p.c_str()))
            return false;
    }

    if (rmdir(path) < 0) {
        return false;
    }
    return true;
}

}
