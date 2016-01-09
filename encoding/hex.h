#ifndef ENCODING_HEX_H_
#define ENCODING_HEX_H_

#include <string>

namespace encoding {
namespace hex {

// Converts hex character |c|.
// If |c| is not hex character the return value is undefined.
int fromHexChar(char c);

// Converts |data| to hex string.
std::string encode(const void* data, size_t len);

} // namespace hex
} // namespace encoding

#endif // ENCODING_HEX_H_
