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

StringPiece trimPrefix(StringPiece s, StringPiece prefix)
{
    if (s.startsWith(prefix))
        return s.substr(prefix.size());
    return s;
}

StringPiece trimSuffix(StringPiece s, StringPiece suffix)
{
    if (s.endsWith(suffix))
        return s.substr(0, s.size() - suffix.size());
    return s;
}

std::string remove(StringPiece s, char cut)
{
    std::string result;
    for (char c : s) {
        if (c == cut)
            continue;
        result.push_back(c);
    }

    return result;
}

} // namespace strings
