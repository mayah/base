#include "encoding/toml/toml.h"

namespace toml {

ParseResult parse(std::istream& is)
{
    Parser parser(is);
    toml::Value v = parser.parse();

    if (v.valid())
        return ParseResult(std::move(v), std::string());

    return ParseResult(std::move(v), std::move(parser.error_reason()));
}

} // namespace toml
