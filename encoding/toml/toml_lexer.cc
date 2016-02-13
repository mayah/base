#include "encoding/toml/toml_lexer.h"

#include <cmath>

#include "base/strings/strings.h"

namespace toml {

bool Lexer::current(char* c)
{
    int x = is_.peek();
    if (x == EOF)
        return false;
    *c = static_cast<char>(x);
    return true;
}

void Lexer::next()
{
    int x = is_.get();
    if (x == '\n')
        ++line_no_;
}

bool Lexer::consume(char c)
{
    char x;
    if (!current(&x))
        return false;
    if (x != c)
        return false;
    next();
    return true;
}

void Lexer::skip_until_newline()
{
    char c;
    while (current(&c)) {
        if (c == '\n')
            return;
        next();
    }
}

Token Lexer::next_string_double_quote()
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

Token Lexer::next_string_single_quote()
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

Token Lexer::next_key()
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

Token Lexer::next_value()
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
        std::stringstream ss(strings::remove(s, '_'));
        std::int64_t x;
        ss >> x;
        return Token(TokenType::INT, x);
    }

    if (isDouble(s)) {
        std::stringstream ss(strings::remove(s, '_'));
        double d;
        ss >> d;
        return Token(TokenType::DOUBLE, d);
    }

    return parse_as_time(s);
}

Token Lexer::parse_as_time(const std::string& str)
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

Token Lexer::next_key_token()
{
    return next_token(false);
}

Token Lexer::next_value_token()
{
    return next_token(true);
}

Token Lexer::next_token(bool isValueToken)
{
    char c;
    while (current(&c)) {
        if (c == ' ' || c == '\t' || c == '\r') {
            next();
            continue;
        }

        if (c == '#') {
            skip_until_newline();
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
            return next_string_double_quote();
        case '\'':
            return next_string_single_quote();
        default:
            if (isValueToken) {
                return next_value();
            } else {
                return next_key();
            }
        }
    }

    return Token(TokenType::END_OF_FILE);
}

} // namespace toml
