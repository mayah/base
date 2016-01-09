#include "encoding/hex.h"

namespace encoding {
namespace hex {

namespace {
const char HEX_TABLE[] = "0123456789ABCDEF";
} // namespace anonymous

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

} // namespace hex
} // namespace encoding
