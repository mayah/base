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
    Token(TokenType type, const std::string& v) : type_(type), strValue_(v) {}
    Token(TokenType type, bool v) : type_(type), intValue_(v) {}
    Token(TokenType type, std::int64_t v) : type_(type), intValue_(v) {}
    Token(TokenType type, double v) : type_(type), doubleValue_(v) {}
    Token(TokenType type, std::chrono::system_clock::time_point tp) : type_(type), timeValue_(tp) {}

    TokenType type() const { return type_; }
    const std::string& strValue() const { return strValue_; }
    bool boolValue() const { return intValue_; }
    std::int64_t intValue() const { return intValue_; }
    double doubleValue() const { return doubleValue_; }
    std::chrono::system_clock::time_point timeValue() const { return timeValue_; }

private:
    TokenType type_;
    std::string strValue_;
    std::int64_t intValue_;
    double doubleValue_;
    std::chrono::system_clock::time_point timeValue_;
};

class Lexer {
public:
    explicit Lexer(std::istream& is) : is_(is), lineNo_(1) {}

    Token nextKeyToken();
    Token nextValueToken();

    int lineNo() const { return lineNo_; }

private:
    bool current(char* c);
    void next();
    bool consume(char c);

    Token nextToken(bool isValueToken);

    void skipUntilNewLine();

    Token nextStringDoubleQuote();
    Token nextStringSingleQuote();

    Token nextKey();
    Token nextValue();

    Token parseAsTime(const std::string&);

    std::istream& is_;
    int lineNo_;
};

} // namespace toml

#endif // ENCODING_TOML_TOML_LEXER_H_
