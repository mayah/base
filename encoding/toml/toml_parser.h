#ifndef ENCODING_TOML_TOML_PARSER_H_
#define ENCODING_TOML_TOML_PARSER_H_

#include "encoding/toml/toml_lexer.h"
#include "encoding/toml/toml_value.h"

namespace toml {

class Parser {
public:
    explicit Parser(std::istream& is) : lexer_(is), token_(TokenType::ERROR) { next_key(); }

    // Parses. If failed, value should be invalid value.
    // You can get the error by calling errorReason().
    Value parse();
    const std::string& error_reason();

private:
    const Token& token() const { return token_; }
    void next_key() { token_ = lexer_.next_key_token(); }
    void next_value() { token_ = lexer_.next_value_token(); }

    void skip_for_key();
    void skip_for_value();

    bool consume_for_key(TokenType);
    bool consume_for_value(TokenType);
    bool consume_EOL_or_EOF_for_key();

    Value* parse_group_key(Value* root);

    bool parse_key_value(Value*);
    bool parse_key(std::string*);
    bool parse_value(Value*);
    bool parse_bool(Value*);
    bool parse_number(Value*);
    bool parse_array(Value*);
    bool parse_inline_table(Value*);

    void add_error(const std::string& reason);

    Lexer lexer_;
    Token token_;
    std::string error_reason_;
};

} // namespace toml

#endif // ENCODING_TOML_TOML_PARSER_H_
