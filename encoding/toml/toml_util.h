#ifndef ENCODING_TOML_TOML_UTIL_H_
#define ENCODING_TOML_TOML_UTIL_H_

#include <string>
#include <sstream>
#include <utility>

#include "base/build_config.h"
#include "base/strings/concat.h"
#include "base/strings/utf8.h"

namespace toml {

namespace internal {

#ifdef OS_WIN
// Windows does not have timegm but have _mkgmtime.
inline time_t timegm(std::tm* timeptr)
{
    return _mkgmtime(timeptr);
}
inline std::tm* gmtime_r(const time_t* timer, std::tm* result)
{
    gmtime_s(result, timer);
    return result;
}
#endif

} // namespace internal

// Converts codepoint to utf8 character.
std::string unescape(const std::string& codepoint);

std::string escape_string(const std::string& s);

bool is_integer(const std::string& s);
bool is_double(const std::string& s);

} // namespace toml

#endif // ENCODING_TOML_TOML_UTIL_H_
