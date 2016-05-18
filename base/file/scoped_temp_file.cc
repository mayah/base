#include "base/file/scoped_temp_file.h"

#include <stdlib.h>

#include "base/file/path.h"
#include "third_party/glog/glog/logging.h"

namespace file {

ScopedTempFile::ScopedTempFile(const char* id) :
    fd_(INVALID_FD)
{
    char buf[4096];
    snprintf(buf, 4095, "/tmp/%s_XXXXXX", id);

    int fd = mkstemp(buf);
    if (fd < 0)
        return;

    path_ = buf;
    fd_ = fd;
}

ScopedTempFile::~ScopedTempFile()
{
    if (fd_ != INVALID_FD) {
        if (close(fd_) < 0) {
            PLOG(WARNING) << "failed to close a temp file: " << path_ << " fd=" << fd_;
        }
    }

    if (unlink(path_.c_str()) < 0) {
        PLOG(WARNING) << "failed to delete a temp file: " << path_;
    }
}

} // namespace file
