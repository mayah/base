#ifndef ENCODING_TOML_TOML_LEXER_H_
#define ENCODING_TOML_TOML_LEXER_H_

#include <chrono>
#include <istream>
#include <string>

#include "encoding/toml/toml_util.h"

namespace toml {

enum class TokenType {
    ERROR,
    END_OF_FILE,
    END_OF_LINE,
    IDENT,
    STRING,
    MULTILINE_STRING,
    BOOL,
    INT,
    DOUBLE,
    TIME,
    COMMA,
    DOT,
    EQUAL,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
};

class Token {
public:
    explicit Token(TokenType type) : type_(type) {}
    Token(TokenType type, const std::string& v) : type_(type), str_value_(v) {}
    Token(TokenType type, bool v) : type_(type), int_value_(v) {}
    Token(TokenType type, std::int64_t v) : type_(type), int_value_(v) {}
    Token(TokenType type, double v) : type_(type), double_value_(v) {}
    Token(TokenType type, std::chrono::system_clock::time_point tp) : type_(type), time_value_(tp) {}

    TokenType type() const { return type_; }
    const std::string& str_value() const { return str_value_; }
    bool bool_value() const { return int_value_; }
    std::int64_t int_value() const { return int_value_; }
    double double_value() const { return double_value_; }
    std::chrono::system_clock::time_point time_value() const { return time_value_; }

private:
    TokenType type_;
    std::string str_value_;
    std::int64_t int_value_;
    double double_value_;
    std::chrono::system_clock::time_point time_value_;
};

class Lexer {
public:
    explicit Lexer(std::istream& is) : is_(is), line_no_(1) {}

    Token next_key_token();
    Token next_value_token();

    int line_no() const { return line_no_; }

private:
    bool current(char* c);
    void next();
    bool consume(char c);

    Token next_token(bool isValueToken);

    void skip_until_newline();

    Token next_string_double_quote();
    Token next_string_single_quote();

    Token next_key();
    Token next_value();

    Token parse_as_time(const std::string&);

    std::istream& is_;
    int line_no_;
};

} // namespace toml

#endif // ENCODING_TOML_TOML_LEXER_H_
