#include "encoding/hex.h"

#include <glog/logging.h>

namespace encoding {
namespace hex {

namespace {
const char HEX_TABLE[] = "0123456789ABCDEF";
} // namespace anonymous

bool is_hex_char(char c)
{
    if ('0' <= c && c <= '9')
        return true;
    if ('A' <= c && c <= 'F')
        return true;
    if ('a' <= c && c <= 'f')
        return true;
    return false;
}

int from_hex_char(char c)
{
    if ('0' <= c && c <= '9')
        return c - '0';
    if ('A' <= c && c <= 'F')
        return c - 'A' + 10;
    if ('a' <= c && c <= 'f')
        return c - 'a' + 10;

    DCHECK(false) << "character c=" << c << " is not a hex character";
    return -1;
}

std::string encode(const void* data, size_t len)
{
    std::string result;
    result.reserve(2 * len);

    const unsigned char* d = static_cast<const unsigned char*>(data);
    for (size_t i = 0; i < len; ++i) {
        unsigned char c = d[i];
        result.push_back(HEX_TABLE[c / 16]);
        result.push_back(HEX_TABLE[c % 16]);
    }
    return result;
}

int decode(strings::StringPiece sp, void* buf)
{
    if (sp.size() % 2 == 1)
        return -1;

    unsigned char* data = static_cast<unsigned char*>(buf);
    int j = 0;
    for (size_t i = 0; i < sp.size(); i += 2) {
        int high = from_hex_char(sp[i]);
        if (high < 0)
            return -1;
        int low = from_hex_char(sp[i + 1]);
        if (low < 0)
            return -1;

        data[j++] = (high << 4) | low;
    }

    return j;
}

} // namespace hex
} // namespace encoding
