#include "base/file/file.h"

#include <fstream>

using namespace std;

namespace file {

bool read_file(strings::StringPiece filename, string* output)
{
    ifstream ifs(filename.as_string(), ios::in | ios::binary);
    if (!ifs)
        return false;

    output->assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    return true;
}

bool write_file(strings::StringPiece filename, const string& data)
{
    ofstream ofs(filename.as_string(), ios::out | ios::binary);
    if (!ofs)
        return false;

    copy(data.begin(), data.end(), ostreambuf_iterator<char>(ofs));
    return ofs.good();
}

} // namespace file
