#include "base/strings/join.h"

namespace strings {

std::string join(const std::vector<std::string>& parts, StringPiece sep)
{
    std::string s;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i > 0)
            s += sep;
        s += parts[i];
    }

    return s;
}

}
