#include "base/file/file.h"

#include <fstream>
#include "base/file/scoped_fd.h"

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

bool copy_file(const char* src, const char* dest)
{
    ScopedFd src_fd = ScopedFd::open_for_read(src);
    if (!src_fd.valid()) {
        PLOG(ERROR) << "failed to open file: " << src;
        return false;
    }

    ScopedFd dest_fd = ScopedFd::open_for_write(dest);
    if (!dest_fd.valid()) {
        PLOG(ERROR) << "failed to open file: " << dest;
        return false;
    }

    bool ok = true;
    const int BUFFER_SIZE = 8192;
    char buf[BUFFER_SIZE];
    while (true) {
        ssize_t len = src_fd.read(buf, BUFFER_SIZE);
        if (len > 0) {
            if (!dest_fd.write_exactly(buf, len)) {
                PLOG(ERROR) << "failed to write: file=" << dest;
            }
            continue;
        }

        if (len == 0) {
            // EOF
            break;
        }

        if (len < 0) {
            if (errno == EAGAIN || errno == EINTR) {
                continue;
            }

            PLOG(ERROR) << "failed to read: file=" << src;
            ok = false;
            break;
        }
    }

    return ok;
}

} // namespace file
