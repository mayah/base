#ifndef BASE_STRINGS_UTF8_H_
#define BASE_STRINGS_UTF8_H_

#include <cstdint>
#include <string>

namespace strings {

// Converts |codepoint| to utf8 string (containing one character).
// If failed, result is empty.
std::string toUTF8(std::uint32_t codepoint);

} // namespace strings

#endif // BASE_STRINGS_UTF8_H_
