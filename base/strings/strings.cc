#include "base/strings/strings.h"

#include <algorithm>

using namespace std;

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

std::string repeat(StringPiece s, int count)
{
    string result;
    result.reserve(s.size() * count);
    for (int i = 0; i < count; ++i) {
        result.append(s.data(), s.size());
    }

    return result;
}

StringPiece trim_space(StringPiece s)
{
    return trim_left(trim_right(s, ' '), ' ');
}

StringPiece trim_left(StringPiece s, char c)
{
    if (s.empty())
        return s;

    StringPiece::size_type pos = s.find_first_not_of(c);
    if (pos == StringPiece::npos)
        return StringPiece();
    return s.substr(pos);
}

StringPiece trim_left(StringPiece s, StringPiece cutset)
{
    if (s.empty() || cutset.empty())
        return s;

    StringPiece::size_type pos = s.find_first_not_of(cutset);
    if (pos == StringPiece::npos)
        return StringPiece();
    return s.substr(pos);
}

StringPiece trim_right(StringPiece s, char c)
{
    if (s.empty())
        return s;

    for (size_t i = s.size(); i > 0; --i) {
        if (s[i - 1] != c)
            return s.substr(0, i);
    }

    return StringPiece();
}

StringPiece trim_right(StringPiece s, StringPiece cutset)
{
    if (s.empty() || cutset.empty())
        return s;

    for (size_t i = s.size(); i > 0; --i) {
        if (cutset.find(s[i - 1]) == StringPiece::npos)
            return s.substr(0, i);
    }

    return StringPiece();
}

StringPiece trim_prefix(StringPiece s, StringPiece prefix)
{
    if (s.starts_with(prefix))
        return s.substr(prefix.size());
    return s;
}

StringPiece trim_suffix(StringPiece s, StringPiece suffix)
{
    if (s.ends_with(suffix))
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

char tolower_ascii(char c)
{
    if (c < 'A' || 'Z' < c)
        return c;
    return c + 'a' - 'A';
}

char toupper_ascii(char c)
{
    if (c < 'a' || 'z' < c)
        return c;
    return c + 'A' - 'a';
}

std::string tolower_ascii(StringPiece s)
{
    std::string result = s.as_string();
    for (auto& c : result) {
        c = tolower_ascii(c);
    }
    return result;
}

std::string toupper_ascii(StringPiece s)
{
    std::string result = s.as_string();
    for (auto& c : result) {
        c = toupper_ascii(c);
    }
    return result;
}

} // namespace strings
