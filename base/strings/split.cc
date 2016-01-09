#include "base/strings/split.h"

namespace strings {

namespace {
template<typename Predicate>
std::vector<std::string> splitInternal(StringPiece str, StringPiece seps, Predicate pred)
{
    std::vector<std::string> result;
    if (str.empty())
        return result;

    size_t start = 0;
    while (start != StringPiece::npos) {
        size_t end = str.find_first_of(seps, start);

        StringPiece piece;
        if (end == StringPiece::npos) {
            piece = str.substr(start);
            start = StringPiece::npos;
        } else {
            piece = str.substr(start, end - start);
            start = end + 1;
        }

        if (pred(piece))
            result.push_back(piece.asString());
    }
    return result;
}

} // namespace anonymous

std::vector<std::string> split(StringPiece str, StringPiece seps)
{
    return splitInternal(str, seps, AllowEmpty());
}

std::vector<std::string> split(StringPiece str, StringPiece seps, AllowEmpty pred)
{
    return splitInternal(str, seps, pred);
}

std::vector<std::string> split(StringPiece str, StringPiece seps, SkipEmpty pred)
{
    return splitInternal(str, seps, pred);
}

} // namespace strings
