#include "base/file/file.h"

#include <fstream>

using namespace std;

namespace file {

bool read_file(const strings::StringPiece& filename, string* output)
{
    ifstream ifs(filename.as_string(), ios::in | ios::binary);
    if (!ifs)
        return false;

    output->assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    return true;
}

} // namespace file
