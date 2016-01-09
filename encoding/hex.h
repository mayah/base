#ifndef ENCODING_HEX_H_
#define ENCODING_HEX_H_

#include <string>

#include "base/strings/string_piece.h"

namespace encoding {
namespace hex {

// Converts hex character |c|.
// If |c| is not hex character the return value is undefined.
int fromHexChar(char c);

// Converts |data| to hex string.
std::string encode(const void* data, size_t len);

// Decodes |sp| to |buf|.
// Returns the length of buf if succeeded, negative number if failed.
// |buf| must have (sp.size() / 2) byte.
int decode(strings::StringPiece sp, void* buf);

} // namespace hex
} // namespace encoding

#endif // ENCODING_HEX_H_
