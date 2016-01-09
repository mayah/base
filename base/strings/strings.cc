#include "base/strings/strings.h"

using namespace std;

namespace strings {

std::string concat(StringPiece s1, StringPiece s2)
{
    std::string s = s1.asString();
    s += s2;
    return s;
}

std::string concat(StringPiece s1, StringPiece s2, StringPiece s3)
{
    std::string s = s1.asString();
    s += s2;
    s += s3;
    return s;
}

std::string repeat(StringPiece s, int count)
{
    string result;
    result.reserve(s.size() * count);
    for (int i = 0; i < count; ++i) {
        result.append(s.data(), s.size());
    }

    return result;
}

StringPiece trimSpace(StringPiece s)
{
    while (!s.empty() && s.front() == ' ')
        s.removePrefix(1);

    while (!s.empty() && s.back() == ' ')
        s.removeSuffix(1);

    return s;
}

} // namespace strings
