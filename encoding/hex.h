#ifndef ENCODING_HEX_H_
#define ENCODING_HEX_H_

#include <string>

namespace encoding {
namespace hex {

std::string encode(const void* data, size_t len);

} // namespace hex
} // namespace encoding

#endif // ENCODING_HEX_H_
