#ifndef BASE_FILE_SCOPED_TEMP_DIR_H_
#define BASE_FILE_SCOPED_TEMP_DIR_H_

#include <string>

namespace file {

// Creates a temporary directory. Useful for testing.
class ScopedTempDir {
public:
    // Creates unique temporary directory.
    explicit ScopedTempDir(const char* id);
    ~ScopedTempDir();

    // Returns true if temporary directory is correctly created.
    explicit operator bool() const { return !directory_path_.empty(); }

    // Returns temporary directory path.
    const std::string& path() const { return directory_path_; }

private:
    std::string directory_path_;
};

} // namespace file

#endif // BASE_FILE_SCOPED_TEMP_DIR_H_
