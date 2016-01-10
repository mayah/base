#ifndef ENCODING_BASE64_H_
#define ENCODING_BASE64_H_

#include <cstddef>
#include <string>

namespace encoding {
namespace base64 {

std::string encode(const void* data, size_t len);

} // namespace base64
} // namespace encoding

#endif // ENCODING_BASE64_H_
