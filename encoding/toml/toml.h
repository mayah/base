#ifndef ENCODING_TOML_TOML_H_
#define ENCODING_TOML_TOML_H_

#include <istream>
#include <string>

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

} // namespace toml

#endif // ENCODING_TOML_TOML_H_
