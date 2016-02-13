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

} // namespace toml

#endif // ENCODING_TOML_TOML_H_
