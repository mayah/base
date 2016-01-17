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
    return trimLeft(trimRight(s, ' '), ' ');
}

StringPiece trimLeft(StringPiece s, char c)
{
    if (s.empty())
        return s;

    StringPiece::size_type pos = s.find_first_not_of(c);
    if (pos == StringPiece::npos)
        return StringPiece();
    return s.substr(pos);
}

StringPiece trimLeft(StringPiece s, StringPiece cutset)
{
    if (s.empty() || cutset.empty())
        return s;

    StringPiece::size_type pos = s.find_first_not_of(cutset);
    if (pos == StringPiece::npos)
        return StringPiece();
    return s.substr(pos);
}

StringPiece trimRight(StringPiece s, char c)
{
    if (s.empty())
        return s;

    for (size_t i = s.size(); i > 0; --i) {
        if (s[i - 1] != c)
            return s.substr(0, i);
    }

    return StringPiece();
}

StringPiece trimRight(StringPiece s, StringPiece cutset)
{
    if (s.empty() || cutset.empty())
        return s;

    for (size_t i = s.size(); i > 0; --i) {
        if (cutset.find(s[i - 1]) == StringPiece::npos)
            return s.substr(0, i);
    }

    return StringPiece();
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
