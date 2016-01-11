#include "encoding/base64.h"

#include <cstdint>
#include <glog/logging.h>

namespace encoding {
namespace base64 {

namespace {
const char ENCODE_TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int32_t decodeChar(uint8_t c)
{
    if ('A' <= c && c <= 'Z')
        return c - 'A';
    if ('a' <= c && c <= 'z')
        return c - 'a' + 26;
    if ('0' <= c && c <= '9')
        return c - '0' + 52;
    if (c == '+')
        return 62;
    if (c == '/')
        return 63;

    return -1;
}

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

size_t decode(strings::StringPiece data, void* buf, size_t size)
{
    if (data.size() % 4 != 0)
        return 0;

    unsigned char* p = static_cast<unsigned char*>(buf);

    size_t pos = 0;
    for (size_t i = 0; i < data.size(); i += 4) {
        if (data[i] == '=' || data[i + 1] == '=') {
            // invalid base64 string.
            return 0;
        }

        if (data[i + 2] == '=') {
            if (pos >= size)
                return 0;
            if (i + 4 != data.size())
                return 0;
            if (data[i + 3] != '=')
                return 0;

            int32_t v1 = decodeChar(data[i]);
            int32_t v2 = decodeChar(data[i + 1]);
            if (v1 < 0 || v2 < 0 || ((v2 & 0x0F) != 0))
                return 0;
            p[pos++] = (v1 << 2) | ((v2 >> 4) & 0x03);
            continue;
        }

        if (data[i + 3] == '=') {
            if (pos + 1 >= size)
                return 0;

            int32_t v1 = decodeChar(data[i]);
            int32_t v2 = decodeChar(data[i + 1]);
            int32_t v3 = decodeChar(data[i + 2]);
            if (v1 < 0 || v2 < 0 || v3 < 0 || ((v3 & 0x03) != 0))
                return 0;
            uint32_t v = (v1 << 12) | (v2 << 6) | (v3 >> 2);
            p[pos++] = (v >> 8) & 0xFF;
            p[pos++] = (v & 0xFF);
            continue;
        }

        if (pos + 2 >= size)
            return 0;
        int32_t v1 = decodeChar(data[i]);
        int32_t v2 = decodeChar(data[i + 1]);
        int32_t v3 = decodeChar(data[i + 2]);
        int32_t v4 = decodeChar(data[i + 3]);
        if (v1 < 0 || v2 < 0 || v3 < 0 || v4 < 0)
            return 0;
        uint32_t v = (v1 << 18) | (v2 << 12) | (v3 << 6) | v4;
        p[pos++] = (v >> 16) & 0xFF;
        p[pos++] = (v >> 8) & 0xFF;
        p[pos++] = v & 0xFF;
    }

    return pos;
}

} // namespace base64
} // namespace encoding
