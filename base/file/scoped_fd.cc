#include "base/file/scoped_fd.h"

#include <fcntl.h>
#include <glog/logging.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace file {

ScopedFd::~ScopedFd()
{
    if (!valid())
        return;

    if (close(fd_) < 0) {
        PLOG(ERROR) << "failed to close: fd=" << fd_;
    }
}

// static
ScopedFd ScopedFd::open_for_read(const char* filename)
{
    int fd = open(filename, O_RDONLY);
    return ScopedFd(fd);
}

// static
ScopedFd ScopedFd::open_for_write(const char* filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    return ScopedFd(fd);
}

ssize_t ScopedFd::read(void* buf, size_t size)
{
    return ::read(fd_, buf, size);
}

bool ScopedFd::read_exactly(void* buf, size_t size)
{
    while (size > 0) {
        ssize_t s = read(buf, size);
        if (s <= 0)
            return false;
        size -= s;
        buf = reinterpret_cast<char*>(buf) + s;
    }

    return true;
}

ssize_t ScopedFd::write(const void* buf, size_t size)
{
    return ::write(fd_, buf, size);
}

bool ScopedFd::write_exactly(const void* buf, size_t size)
{
    while (size > 0) {
        ssize_t s = write(buf, size);
        if (s <= 0)
            return false;
        size -= s;
        buf = reinterpret_cast<const char*>(buf) + s;
    }

    return true;
}

bool ScopedFd::write_exactly(strings::StringPiece sp)
{
    return write_exactly(sp.data(), sp.size());
}

} // namespace file
