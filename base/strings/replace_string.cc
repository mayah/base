#include "base/strings/replace_string.h"

namespace strings {

std::string replace_string(StringPiece s, StringPiece oldsub, StringPiece newsub, OneOrAll one_or_all)
{
    if (oldsub.empty())
        return s.as_string();

    std::string result;

    StringPiece::size_type start_pos = 0;
    StringPiece::size_type pos;
    do {
        pos = s.find(oldsub, start_pos);
        if (pos == StringPiece::npos)
            break;

        result.append(s.data() + start_pos, pos - start_pos);
        result.append(newsub.data(), newsub.length());
        start_pos = pos + oldsub.length();
    } while (one_or_all == OneOrAll::ALL);

    result.append(s.data() + start_pos, s.length() - start_pos);
    return result;
}

} // namespace strings
