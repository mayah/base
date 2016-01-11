#ifndef ENCODING_BASE64_H_
#define ENCODING_BASE64_H_

#include <cstddef>
#include <string>

#include "base/strings/string_piece.h"

namespace encoding {
namespace base64 {

std::string encode(const void* data, size_t len);

// Decodes |data|, and saves the data to |buf|, which has |size| size.
// Returns the length of data if all |data| is correctly decoded to |buf|.
// Returns 0 otherwise. If |data| does not contain any data, 0 will be returned.
size_t decode(strings::StringPiece data, void* buf, size_t size);

} // namespace base64
} // namespace encoding

#endif // ENCODING_BASE64_H_
