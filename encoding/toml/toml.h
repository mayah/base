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

namespace internal {

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

// ----------------------------------------------------------------------
// Implementations

// ----------------------------------------------------------------------
// Lexer

namespace internal {

inline bool Lexer::current(char* c)
{
    int x = is_.peek();
    if (x == EOF)
        return false;
    *c = static_cast<char>(x);
    return true;
}

inline void Lexer::next()
{
    int x = is_.get();
    if (x == '\n')
        ++lineNo_;
}

inline bool Lexer::consume(char c)
{
    char x;
    if (!current(&x))
        return false;
    if (x != c)
        return false;
    next();
    return true;
}

inline void Lexer::skipUntilNewLine()
{
    char c;
    while (current(&c)) {
        if (c == '\n')
            return;
        next();
    }
}

inline Token Lexer::nextStringDoubleQuote()
{
    if (!consume('"'))
        return Token(TokenType::ERROR, std::string("string didn't start with '\"'"));

    std::string s;
    char c;
    bool multiline = false;

    if (current(&c) && c == '"') {
        next();
        if (!current(&c) || c != '"') {
            // OK. It's empty string.
            return Token(TokenType::STRING, std::string());
        }

        next();
        // raw string literal started.
        // Newline just after """ should be ignored.
        while (current(&c) && (c == ' ' || c == '\t'))
            next();
        if (current(&c) && c == '\n')
            next();
        multiline = true;
    }

    while (current(&c)) {
        next();
        if (c == '\\') {
            if (!current(&c))
                return Token(TokenType::ERROR, std::string("string has unknown escape sequence"));
            next();
            switch (c) {
            case 't': c = '\t'; break;
            case 'n': c = '\n'; break;
            case 'r': c = '\r'; break;
            case 'u':
            case 'U': {
                int size = c == 'u' ? 4 : 8;
                std::string codepoint;
                for (int i = 0; i < size; ++i) {
                  if (current(&c) && (('0' <= c && c <= '9') || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f'))) {
                    codepoint += c;
                    next();
                  } else {
                    return Token(TokenType::ERROR, std::string("string has unknown escape sequence"));
                  }
                }
                s += unescape(codepoint);
                continue;
            }
            case '"': c = '"'; break;
            case '\'': c = '\''; break;
            case '\\': c = '\\'; break;
            case '\n':
                while (current(&c) && (c == ' ' || c == '\t' || c == '\r' || c == '\n')) {
                    next();
                }
                continue;
            default:
                return Token(TokenType::ERROR, std::string("string has unknown escape sequence"));
            }
        } else if (c == '"') {
            if (multiline) {
                if (current(&c) && c == '"') {
                    next();
                    if (current(&c) && c == '"') {
                        next();
                        return Token(TokenType::MULTILINE_STRING, s);
                    } else {
                        s += '"';
                        s += '"';
                        continue;
                    }
                } else {
                    s += '"';
                    continue;
                }
            } else {
                return Token(TokenType::STRING, s);
            }
        }

        s += c;
    }

    return Token(TokenType::ERROR, std::string("string didn't end"));
}

inline Token Lexer::nextStringSingleQuote()
{
    if (!consume('\''))
        return Token(TokenType::ERROR, std::string("string didn't start with '\''?"));

    std::string s;
    char c;

    if (current(&c) && c == '\'') {
        next();
        if (!current(&c) || c != '\'') {
            // OK. It's empty string.
            return Token(TokenType::STRING, std::string());
        }
        next();
        // raw string literal started.
        // Newline just after """ should be ignored.
        if (current(&c) && c == '\n')
            next();

        while (current(&c)) {
            if (c == '\'') {
                next();
                if (current(&c) && c == '\'') {
                    next();
                    if (current(&c) && c == '\'') {
                        next();
                        return Token(TokenType::MULTILINE_STRING, s);
                    } else {
                        s += '\'';
                        s += '\'';
                        continue;
                    }
                } else {
                    s += '\'';
                    continue;
                }
            }

            next();
            s += c;
            continue;
        }

        return Token(TokenType::ERROR, std::string("string didn't end with '\'\'\'' ?"));
    }

    while (current(&c)) {
        next();
        if (c == '\'') {
            return Token(TokenType::STRING, s);
        }

        s += c;
    }

    return Token(TokenType::ERROR, std::string("string didn't end with '\''?"));
}

inline Token Lexer::nextKey()
{
    std::string s;
    char c;
    while (current(&c) && (isalnum(c) || c == '_' || c == '-')) {
        s += c;
        next();
    }

    if (s.empty())
        return Token(TokenType::ERROR, std::string("Unknown key format"));

    return Token(TokenType::IDENT, s);
}

inline Token Lexer::nextValue()
{
    std::string s;
    char c;

    if (current(&c) && isalpha(c)) {
        s += c;
        next();
        while (current(&c) && isalpha(c)) {
            s += c;
            next();
        }

        if (s == "true")
            return Token(TokenType::BOOL, true);
        if (s == "false")
            return Token(TokenType::BOOL, false);
        return Token(TokenType::ERROR, std::string("Unknown ident: ") + s);
    }

    while (current(&c) && (('0' <= c && c <= '9') || c == '.' || c == 'e' || c == 'E' ||
                           c == 'T' || c == 'Z' || c == '_' || c == ':' || c == '-' || c == '+')) {
        next();
        s += c;
    }

    if (isInteger(s)) {
        std::stringstream ss(removeDelimiter(s));
        std::int64_t x;
        ss >> x;
        return Token(TokenType::INT, x);
    }

    if (isDouble(s)) {
        std::stringstream ss(removeDelimiter(s));
        double d;
        ss >> d;
        return Token(TokenType::DOUBLE, d);
    }

    return parseAsTime(s);
}

inline Token Lexer::parseAsTime(const std::string& str)
{
    const char* s = str.c_str();

    int n;
    int YYYY, MM, DD;
    if (sscanf(s, "%d-%d-%d%n", &YYYY, &MM, &DD, &n) != 3)
        return Token(TokenType::ERROR, std::string("Invalid token"));

    if (s[n] == '\0') {
        std::tm t;
        t.tm_sec = 0;
        t.tm_min = 0;
        t.tm_hour = 0;
        t.tm_mday = DD;
        t.tm_mon = MM - 1;
        t.tm_year = YYYY - 1900;
        auto tp = std::chrono::system_clock::from_time_t(timegm(&t));
        return Token(TokenType::TIME, tp);
    }

    if (s[n] != 'T')
        return Token(TokenType::ERROR, std::string("Invalid token"));

    s = s + n + 1;

    int hh, mm;
    double ss; // double for fraction
    if (sscanf(s, "%d:%d:%lf%n", &hh, &mm, &ss, &n) != 3)
        return Token(TokenType::ERROR, std::string("Invalid token"));

    std::tm t;
    t.tm_sec = static_cast<int>(ss);
    t.tm_min = mm;
    t.tm_hour = hh;
    t.tm_mday = DD;
    t.tm_mon = MM - 1;
    t.tm_year = YYYY - 1900;
    auto tp = std::chrono::system_clock::from_time_t(timegm(&t));
    ss -= static_cast<int>(ss);
    tp += std::chrono::microseconds(static_cast<int>(std::round(ss * 1000000)));

    if (s[n] == '\0')
        return Token(TokenType::TIME, tp);

    if (s[n] == 'Z' && s[n + 1] == '\0')
        return Token(TokenType::TIME, tp);

    s = s + n;
    // offset
    // [+/-]%d:%d
    char pn;
    int oh, om;
    if (sscanf(s, "%c%d:%d", &pn, &oh, &om) != 3)
        return Token(TokenType::ERROR, std::string("Invalid token"));

    if (pn != '+' && pn != '-')
        return Token(TokenType::ERROR, std::string("Invalid token"));

    if (pn == '+') {
        tp -= std::chrono::hours(oh);
        tp -= std::chrono::minutes(om);
    } else {
        tp += std::chrono::hours(oh);
        tp += std::chrono::minutes(om);
    }

    return Token(TokenType::TIME, tp);
}

inline Token Lexer::nextKeyToken()
{
    return nextToken(false);
}

inline Token Lexer::nextValueToken()
{
    return nextToken(true);
}

inline Token Lexer::nextToken(bool isValueToken)
{
    char c;
    while (current(&c)) {
        if (c == ' ' || c == '\t' || c == '\r') {
            next();
            continue;
        }

        if (c == '#') {
            skipUntilNewLine();
            continue;
        }

        switch (c) {
        case '\n':
            next();
            return Token(TokenType::END_OF_LINE);
        case '=':
            next();
            return Token(TokenType::EQUAL);
        case '{':
            next();
            return Token(TokenType::LBRACE);
        case '}':
            next();
            return Token(TokenType::RBRACE);
        case '[':
            next();
            return Token(TokenType::LBRACKET);
        case ']':
            next();
            return Token(TokenType::RBRACKET);
        case ',':
            next();
            return Token(TokenType::COMMA);
        case '.':
            next();
            return Token(TokenType::DOT);
        case '\"':
            return nextStringDoubleQuote();
        case '\'':
            return nextStringSingleQuote();
        default:
            if (isValueToken) {
                return nextValue();
            } else {
                return nextKey();
            }
        }
    }

    return Token(TokenType::END_OF_FILE);
}

} // namespace internal

namespace internal {

inline void Parser::skipForKey()
{
    while (token().type() == TokenType::END_OF_LINE)
        nextKey();
}

inline void Parser::skipForValue()
{
    while (token().type() == TokenType::END_OF_LINE)
        nextValue();
}

inline bool Parser::consumeForKey(TokenType type)
{
    if (token().type() == type) {
        nextKey();
        return true;
    }

    return false;
}

inline bool Parser::consumeForValue(TokenType type)
{
    if (token().type() == type) {
        nextValue();
        return true;
    }

    return false;
}

inline bool Parser::consumeEOLorEOFForKey()
{
    if (token().type() == TokenType::END_OF_LINE || token().type() == TokenType::END_OF_FILE) {
        nextKey();
        return true;
    }

    return false;
}

inline void Parser::addError(const std::string& reason)
{
    if (!errorReason_.empty())
        return;

    std::stringstream ss;
    ss << "Error: line " << lexer_.lineNo() << ": " << reason;
    errorReason_ = ss.str();
}

inline const std::string& Parser::errorReason()
{
    return errorReason_;
}

inline Value Parser::parse()
{
    Value root((Table()));
    Value* currentValue = &root;

    while (true) {
        skipForKey();
        if (token().type() == TokenType::END_OF_FILE)
            break;
        if (token().type() == TokenType::LBRACKET) {
            currentValue = parseGroupKey(&root);
            if (!currentValue) {
                addError("error when parsing group key");
                return Value();
            }
            continue;
        }

        if (!parseKeyValue(currentValue)) {
            addError("error when parsing key Value");
            return Value();
        }
    }
    return root;
}

inline Value* Parser::parseGroupKey(Value* root)
{
    if (!consumeForKey(TokenType::LBRACKET))
        return nullptr;

    bool isArray = false;
    if (token().type() == TokenType::LBRACKET) {
        nextKey();
        isArray = true;
    }

    Value* currentValue = root;
    while (true) {
        if (token().type() != TokenType::IDENT && token().type() != TokenType::STRING)
            return nullptr;

        std::string key = token().strValue();
        nextKey();

        if (token().type() == TokenType::DOT) {
            nextKey();
            if (Value* candidate = currentValue->find_child(key)) {
                if (candidate->is<Array>() && candidate->size() > 0)
                    candidate = candidate->find(candidate->size() - 1);
                if (!candidate->is<Table>())
                    return nullptr;
                currentValue = candidate;
            } else {
                currentValue = currentValue->set_child(key, Table());
            }
            continue;
        }

        if (token().type() == TokenType::RBRACKET) {
            nextKey();
            if (Value* candidate = currentValue->find_child(key)) {
                if (isArray) {
                    if (!candidate->is<Array>())
                        return nullptr;
                    currentValue = candidate->push(Table());
                } else {
                    if (candidate->is<Array>() && candidate->size() > 0)
                        candidate = candidate->find(candidate->size() - 1);
                    if (!candidate->is<Table>())
                        return nullptr;
                    currentValue = candidate;
                }
            } else {
                if (isArray) {
                    currentValue = currentValue->set_child(key, Array());
                    currentValue = currentValue->push(Table());
                } else {
                    currentValue = currentValue->set_child(key, Table());
                }
            }
            break;
        }

        return nullptr;
    }

    if (isArray) {
        if (!consumeForKey(TokenType::RBRACKET))
            return nullptr;
    }

    if (!consumeEOLorEOFForKey())
        return nullptr;

    return currentValue;
}

inline bool Parser::parseKeyValue(Value* current)
{
    std::string key;
    if (!parseKey(&key)) {
        addError("parse key failed");
        return false;
    }
    if (!consumeForValue(TokenType::EQUAL)) {
        addError("no equal?");
        return false;
    }

    Value v;
    if (!parseValue(&v))
        return false;
    if (!consumeEOLorEOFForKey())
        return false;

    if (current->has(key)) {
        addError("Multiple same key: " + key);
        return false;
    }

    current->set_child(key, std::move(v));
    return true;
}

inline bool Parser::parseKey(std::string* key)
{
    key->clear();

    if (token().type() == TokenType::IDENT || token().type() == TokenType::STRING) {
        *key = token().strValue();
        nextValue();
        return true;
    }

    return false;
}

inline bool Parser::parseValue(Value* v)
{
    switch (token().type()) {
    case TokenType::STRING:
    case TokenType::MULTILINE_STRING:
        *v = token().strValue();
        nextValue();
        return true;
    case TokenType::LBRACKET:
        return parseArray(v);
    case TokenType::LBRACE:
        return parseInlineTable(v);
    case TokenType::BOOL:
        *v = token().boolValue();
        nextValue();
        return true;
    case TokenType::INT:
        *v = token().intValue();
        nextValue();
        return true;
    case TokenType::DOUBLE:
        *v = token().doubleValue();
        nextValue();
        return true;
    case TokenType::TIME:
        *v = token().timeValue();
        nextValue();
        return true;
    case TokenType::ERROR:
        addError(token().strValue());
        return false;
    default:
        addError("unexpected token");
        return false;
    }
}

inline bool Parser::parseBool(Value* v)
{
    if (token().strValue() == "true") {
        nextValue();
        *v = true;
        return true;
    }

    if (token().strValue() == "false") {
        nextValue();
        *v = false;
        return true;
    }

    return false;
}

inline bool Parser::parseArray(Value* v)
{
    if (!consumeForValue(TokenType::LBRACKET))
        return false;

    Array a;
    while (true) {
        skipForValue();

        if (token().type() == TokenType::RBRACKET)
            break;

        skipForValue();
        Value x;
        if (!parseValue(&x))
            return false;

        if (!a.empty()) {
            if (a.front().type() != x.type()) {
                addError("type check failed");
                return false;
            }
        }

        a.push_back(std::move(x));
        skipForValue();
        if (token().type() == TokenType::RBRACKET)
            break;
        if (token().type() == TokenType::COMMA)
            nextValue();
    }

    if (!consumeForValue(TokenType::RBRACKET))
        return false;
    *v = std::move(a);
    return true;
}

inline bool Parser::parseInlineTable(Value* value)
{
    // For inline table, next is KEY, so use consumeForKey here.
    if (!consumeForKey(TokenType::LBRACE))
        return false;

    Value t((Table()));
    bool first = true;
    while (true) {
        if (token().type() == TokenType::RBRACE) {
            break;
        }

        if (!first) {
            if (token().type() != TokenType::COMMA) {
                addError("inline table didn't have ',' for delimiter?");
                return false;
            }
            nextKey();
        }
        first = false;

        std::string key;
        if (!parseKey(&key))
            return false;
        if (!consumeForValue(TokenType::EQUAL))
            return false;
        Value v;
        if (!parseValue(&v))
            return false;

        if (t.has(key)) {
            addError("inline table has multiple same keys: key=" + key);
            return false;
        }

        t.set(key, v);
    }

    if (!consumeForValue(TokenType::RBRACE))
        return false;
    *value = std::move(t);
    return true;
}

} // namespace internal
} // namespace toml

#endif // ENCODING_TOML_TOML_H_
