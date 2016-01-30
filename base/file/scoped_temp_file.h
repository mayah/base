#ifndef BASE_FILE_SCOPED_TEMP_FILE_H_
#define BASE_FILE_SCOPED_TEMP_FILE_H_

#include <string>

namespace file {

// Creates a temporary file and open it.
// If failed, path is empty.
class ScopedTempFile {
public:
    static const int INVALID_FD = -1;

    explicit ScopedTempFile(const char* id);
    ~ScopedTempFile();

    explicit operator bool() const { return !path_.empty(); }
    // Returns temporary directory path.
    const std::string& path() const { return path_; }
    // Returns file descriptor. If not valid, invalid file descriptor.
    int fd() const { return fd_; }

private:
    std::string path_;
    int fd_;
};

} // namespace file

#endif // BASE_FILE_SCOPED_TEMP_FILE_H_
