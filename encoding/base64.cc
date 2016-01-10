#include "encoding/base64.h"

#include <glog/logging.h>

namespace encoding {
namespace base64 {

namespace {
    const char ENCODE_TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
} // namespace

std::string encode(const void* data, size_t len)
{
    std::string result;
    result.reserve(len * 4 / 3 + 1);

    const unsigned char* p = static_cast<const unsigned char*>(data);

    size_t i = 0;
    for (; i + 3 <= len; i += 3) {
        int c1 = (p[i] & 0xFC) >> 2;
        int c2 = ((p[i] & 0x03) << 4) + ((p[i + 1] & 0xF0) >> 4);
        int c3 = ((p[i + 1] & 0x0F) << 2) + ((p[i + 2] & 0xC0) >> 6);
        int c4 = p[i + 2] & 0x3F;

        result.push_back(ENCODE_TABLE[c1]);
        result.push_back(ENCODE_TABLE[c2]);
        result.push_back(ENCODE_TABLE[c3]);
        result.push_back(ENCODE_TABLE[c4]);
    }

    switch (len - i) {
    case 0:
        break;
    case 1: {
        int c1 = (p[i] & 0xFC) >> 2;
        int c2 = ((p[i] & 0x03) << 4);
        result.push_back(ENCODE_TABLE[c1]);
        result.push_back(ENCODE_TABLE[c2]);
        result.push_back('=');
        result.push_back('=');
        break;
    }
    case 2: {
        int c1 = (p[i] & 0xFC) >> 2;
        int c2 = ((p[i] & 0x03) << 4) + ((p[i + 1] & 0xF0) >> 4);
        int c3 = ((p[i + 1] & 0x0F) << 2);
        result.push_back(ENCODE_TABLE[c1]);
        result.push_back(ENCODE_TABLE[c2]);
        result.push_back(ENCODE_TABLE[c3]);
        result.push_back('=');
        break;
    }
    default:
        CHECK(false) << "unexpected i=" << i << " len=" << len;
    }

    return result;
}

} // namespace base64
} // namespace encoding
