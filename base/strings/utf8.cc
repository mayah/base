#include "base/strings/utf8.h"

namespace strings {

std::string toUTF8(std::uint32_t x)
{
    if (x <= 0x7FU) {
        // 0xxxxxxx
        return std::string({static_cast<char>(x)});
    }

    if (x <= 0x7FFU) {
        // 110yyyyx 10xxxxxx
        return std::string({
            static_cast<char>(0xC0 | ((x >> 6) & 0xDF)),
            static_cast<char>(0x80 | ((x >> 0) & 0xBF)),
        });
    }

    if (x <= 0xFFFFU) {
        // 1110yyyy 10yxxxxx 10xxxxxx
        return std::string({
            static_cast<char>(0xE0 | ((x >> 12) & 0xEF)),
            static_cast<char>(0x80 | ((x >> 6) & 0xBF)),
            static_cast<char>(0x80 | ((x >> 0) & 0xBF)),
        });
    }

    if (x <= 0x10FFFFU) {
        // 11110yyy 10yyxxxx 10xxxxxx 10xxxxxx
        return std::string({
            static_cast<char>(0xF0 | ((x >> 18) & 0xF7)),
            static_cast<char>(0x80 | ((x >> 12) & 0xBF)),
            static_cast<char>(0x80 | ((x >> 6) & 0xBF)),
            static_cast<char>(0x80 | ((x >> 0) & 0xBF)),
        });
    }

    return std::string();
}

} // namespace strings
