#ifndef ENCODING_TOML_TOML_PARSER_H_
#define ENCODING_TOML_TOML_PARSER_H_

#include "encoding/toml/toml_lexer.h"
#include "encoding/toml/toml_value.h"

namespace toml {
namespace internal {

class Parser {
public:
    explicit Parser(std::istream& is) : lexer_(is), token_(TokenType::ERROR) { nextKey(); }

    // Parses. If failed, value should be invalid value.
    // You can get the error by calling errorReason().
    Value parse();
    const std::string& errorReason();

private:
    const Token& token() const { return token_; }
    void nextKey() { token_ = lexer_.nextKeyToken(); }
    void nextValue() { token_ = lexer_.nextValueToken(); }

    void skipForKey();
    void skipForValue();

    bool consumeForKey(TokenType);
    bool consumeForValue(TokenType);
    bool consumeEOLorEOFForKey();

    Value* parseGroupKey(Value* root);

    bool parseKeyValue(Value*);
    bool parseKey(std::string*);
    bool parseValue(Value*);
    bool parseBool(Value*);
    bool parseNumber(Value*);
    bool parseArray(Value*);
    bool parseInlineTable(Value*);

    void addError(const std::string& reason);

    Lexer lexer_;
    Token token_;
    std::string errorReason_;
};

} // namespace internal
} // namespace toml

#endif // ENCODING_TOML_TOML_PARSER_H_
