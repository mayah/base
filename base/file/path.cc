#include "base/file/path.h"

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
