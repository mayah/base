#ifndef BASE_FILE_SCOPED_FD_H_
#define BASE_FILE_SCOPED_FD_H_

#include <sys/types.h>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/strings/string_piece.h"

namespace file {

class ScopedFd {
public:
    explicit ScopedFd(int fd = INVALID_FD) : fd_(fd) {}
    ScopedFd(ScopedFd&& fd);
    ~ScopedFd();

    static ScopedFd open_for_read(const char* filename);
    // Opens a file for writing. The content will be truncated.
    static ScopedFd open_for_write(const char* filename);

    ScopedFd& operator=(ScopedFd&&);

    bool valid() const { return fd_ != INVALID_FD; }
    int get() const { return fd_; }

    ssize_t read(void* buf, size_t size) WARN_UNUSED_RESULT;
    bool read_exactly(void* buf, size_t size) WARN_UNUSED_RESULT;

    ssize_t write(const void* buf, size_t size) WARN_UNUSED_RESULT;
    bool write_exactly(const void* buf, size_t size) WARN_UNUSED_RESULT;
    bool write_exactly(strings::StringPiece sp) WARN_UNUSED_RESULT;

private:
    static const int INVALID_FD = -1;

    int fd_;

    DISALLOW_COPY_AND_ASSIGN(ScopedFd);
};

} // namespace file

#endif // BASE_FILE_SCOPED_FD_H_
