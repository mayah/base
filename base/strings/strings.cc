#include "base/strings/strings.h"

#include <algorithm>

#include "base/strings/ascii_ctype.h"

using namespace std;

namespace strings {

std::string repeat(StringPiece s, int count)
{
    string result;
    result.reserve(s.size() * count);
    for (int i = 0; i < count; ++i) {
        result.append(s.data(), s.size());
    }

    return result;
}

std::string pad_left(StringPiece s, size_t n, char c)
{
    if (s.size() >= n)
        return s.as_string();

    size_t count = n - s.size();
    return std::string(count, c) + s.as_string();
}

std::string pad_right(StringPiece s, size_t n, char c)
{
    if (s.size() >= n)
        return s.as_string();

    size_t count = n - s.size();
    return s.as_string() + std::string(count, c);
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
