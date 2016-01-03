#include "base/file/path.h"

namespace file {

bool isAbsolutePath(strings::StringPiece path)
{
    return !path.empty() && path[0] == '/';
}

}
