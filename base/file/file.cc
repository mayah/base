#include "base/file/file.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>

using namespace std;

namespace file {

bool is_directory(const char* path)
{
    struct stat st;
    if (stat(path, &st) < 0)
        return false;

    return S_ISDIR(st.st_mode);
}

bool read_file(const strings::StringPiece& filename, string* output)
{
    ifstream ifs(filename.as_string(), ios::in | ios::binary);
    if (!ifs)
        return false;

    output->assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    return true;
}

} // namespace file
