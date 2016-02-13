#include "encoding/toml/toml_util.h"

namespace toml {

std::string unescape(const std::string& codepoint)
{
    std::stringstream ss(codepoint);

    std::uint32_t x;
    ss >> std::hex >> x;
    return strings::to_utf8(x);
}

std::string escape_string(const std::string& s)
{
    std::stringstream ss;
    for (size_t i = 0; i < s.size(); ++i) {
        switch (s[i]) {
        case '\n': ss << "\\n"; break;
        case '\r': ss << "\\r"; break;
        case '\t': ss << "\\t"; break;
        case '\"': ss << "\\\""; break;
        case '\'': ss << "\\\'"; break;
        case '\\': ss << "\\\\"; break;
        default: ss << s[i]; break;
        }
    }

    return ss.str();
}

// Returns true if |s| is integer.
// [+-]?\d+(_\d+)*
bool is_integer(const std::string& s)
{
    if (s.empty())
        return false;

    std::string::size_type p = 0;
    if (s[p] == '+' || s[p] == '-')
        ++p;

    while (p < s.size() && '0' <= s[p] && s[p] <= '9') {
        ++p;
        if (p < s.size() && s[p] == '_') {
            ++p;
            if (!(p < s.size() && '0' <= s[p] && s[p] <= '9'))
                return false;
        }
    }

    return p == s.size();
}

// Returns true if |s| is double.
// [+-]? (\d+(_\d+)*)? (\.\d+(_\d+)*)? ([eE] [+-]? \d+(_\d+)*)?
//       1-----------  2-------------  3----------------------
// 2 or (1 and 3) should exist.
bool is_double(const std::string& s)
{
    if (s.empty())
        return false;

    std::string::size_type p = 0;
    if (s[p] == '+' || s[p] == '-')
        ++p;

    bool ok = false;
    while (p < s.size() && '0' <= s[p] && s[p] <= '9') {
        ++p;
        ok = true;

        if (p < s.size() && s[p] == '_') {
            ++p;
            if (!(p < s.size() && '0' <= s[p] && s[p] <= '9'))
                return false;
        }
    }

    if (p < s.size() && s[p] == '.')
        ++p;

    while (p < s.size() && '0' <= s[p] && s[p] <= '9') {
        ++p;
        ok = true;

        if (p < s.size() && s[p] == '_') {
            ++p;
            if (!(p < s.size() && '0' <= s[p] && s[p] <= '9'))
                return false;
        }
    }

    if (!ok)
        return false;

    ok = false;
    if (p < s.size() && (s[p] == 'e' || s[p] == 'E')) {
        ++p;
        if (p < s.size() && (s[p] == '+' || s[p] == '-'))
            ++p;
        while (p < s.size() && '0' <= s[p] && s[p] <= '9') {
            ++p;
            ok = true;

            if (p < s.size() && s[p] == '_') {
                ++p;
                if (!(p < s.size() && '0' <= s[p] && s[p] <= '9'))
                    return false;
            }
        }
        if (!ok)
            return false;
    }

    return p == s.size();
}

} // namespace toml
