#ifndef ENCODING_TOML_TOML_H_
#define ENCODING_TOML_TOML_H_

#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "encoding/toml/toml_lexer.h"
#include "encoding/toml/toml_parser.h"
#include "encoding/toml/toml_util.h"
#include "encoding/toml/toml_value.h"

namespace toml {

// parse() returns ParseResult.
struct ParseResult {
    ParseResult(toml::Value v, std::string er) :
        value(std::move(v)),
        errorReason(std::move(er)) {}

    bool valid() const { return value.valid(); }

    toml::Value value;
    std::string errorReason;
};

// Parses from std::istream.
ParseResult parse(std::istream&);

// ----------------------------------------------------------------------
// Declarations for Implementations
//   You don't need to understand the below to use this library.

namespace internal {

#if defined(_MSC_VER)
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

} // namespace toml

#endif // ENCODING_TOML_TOML_H_
