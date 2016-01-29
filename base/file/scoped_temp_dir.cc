#include "base/file/scoped_temp_dir.h"

#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "base/file/path.h"

namespace file {

ScopedTempDir::ScopedTempDir(const char* id)
{
    char tmpdir[PATH_MAX];
    snprintf(tmpdir, sizeof(tmpdir), "/tmp/%s_%d", id, getpid());
    if (mkdir(tmpdir, 0777) < 0) {
        // failed to create tempdir.
        return;
    }

    directory_path_ = tmpdir;
}

ScopedTempDir::~ScopedTempDir()
{
    if (!directory_path_.empty())
        delete_tree(directory_path_.c_str());
}


} // namespace file
