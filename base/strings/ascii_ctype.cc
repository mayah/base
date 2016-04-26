#include "base/strings/ascii_ctype.h"

namespace strings {

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

} // namespace strings
