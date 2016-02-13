#include "encoding/toml/toml_parser.h"

namespace toml {

void Parser::skip_for_key()
{
    while (token().type() == TokenType::END_OF_LINE)
        next_key();
}

void Parser::skip_for_value()
{
    while (token().type() == TokenType::END_OF_LINE)
        next_value();
}

bool Parser::consume_for_key(TokenType type)
{
    if (token().type() == type) {
        next_key();
        return true;
    }

    return false;
}

bool Parser::consume_for_value(TokenType type)
{
    if (token().type() == type) {
        next_value();
        return true;
    }

    return false;
}

bool Parser::consume_EOL_or_EOF_for_key()
{
    if (token().type() == TokenType::END_OF_LINE || token().type() == TokenType::END_OF_FILE) {
        next_key();
        return true;
    }

    return false;
}

void Parser::add_error(const std::string& reason)
{
    if (!error_reason_.empty())
        return;

    std::stringstream ss;
    ss << "Error: line " << lexer_.line_no() << ": " << reason;
    error_reason_ = ss.str();
}

const std::string& Parser::error_reason()
{
    return error_reason_;
}

Value Parser::parse()
{
    Value root((Table()));
    Value* currentValue = &root;

    while (true) {
        skip_for_key();
        if (token().type() == TokenType::END_OF_FILE)
            break;
        if (token().type() == TokenType::LBRACKET) {
            currentValue = parse_group_key(&root);
            if (!currentValue) {
                add_error("error when parsing group key");
                return Value();
            }
            continue;
        }

        if (!parse_key_value(currentValue)) {
            add_error("error when parsing key Value");
            return Value();
        }
    }
    return root;
}

Value* Parser::parse_group_key(Value* root)
{
    if (!consume_for_key(TokenType::LBRACKET))
        return nullptr;

    bool isArray = false;
    if (token().type() == TokenType::LBRACKET) {
        next_key();
        isArray = true;
    }

    Value* currentValue = root;
    while (true) {
        if (token().type() != TokenType::IDENT && token().type() != TokenType::STRING)
            return nullptr;

        std::string key = token().str_value();
        next_key();

        if (token().type() == TokenType::DOT) {
            next_key();
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
            next_key();
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
        if (!consume_for_key(TokenType::RBRACKET))
            return nullptr;
    }

    if (!consume_EOL_or_EOF_for_key())
        return nullptr;

    return currentValue;
}

bool Parser::parse_key_value(Value* current)
{
    std::string key;
    if (!parse_key(&key)) {
        add_error("parse key failed");
        return false;
    }
    if (!consume_for_value(TokenType::EQUAL)) {
        add_error("no equal?");
        return false;
    }

    Value v;
    if (!parse_value(&v))
        return false;
    if (!consume_EOL_or_EOF_for_key())
        return false;

    if (current->has(key)) {
        add_error("Multiple same key: " + key);
        return false;
    }

    current->set_child(key, std::move(v));
    return true;
}

bool Parser::parse_key(std::string* key)
{
    key->clear();

    if (token().type() == TokenType::IDENT || token().type() == TokenType::STRING) {
        *key = token().str_value();
        next_value();
        return true;
    }

    return false;
}

bool Parser::parse_value(Value* v)
{
    switch (token().type()) {
    case TokenType::STRING:
    case TokenType::MULTILINE_STRING:
        *v = token().str_value();
        next_value();
        return true;
    case TokenType::LBRACKET:
        return parse_array(v);
    case TokenType::LBRACE:
        return parse_inline_table(v);
    case TokenType::BOOL:
        *v = token().bool_value();
        next_value();
        return true;
    case TokenType::INT:
        *v = token().int_value();
        next_value();
        return true;
    case TokenType::DOUBLE:
        *v = token().double_value();
        next_value();
        return true;
    case TokenType::TIME:
        *v = token().time_value();
        next_value();
        return true;
    case TokenType::ERROR:
        add_error(token().str_value());
        return false;
    default:
        add_error("unexpected token");
        return false;
    }
}

bool Parser::parse_bool(Value* v)
{
    if (token().str_value() == "true") {
        next_value();
        *v = true;
        return true;
    }

    if (token().str_value() == "false") {
        next_value();
        *v = false;
        return true;
    }

    return false;
}

bool Parser::parse_array(Value* v)
{
    if (!consume_for_value(TokenType::LBRACKET))
        return false;

    Array a;
    while (true) {
        skip_for_value();

        if (token().type() == TokenType::RBRACKET)
            break;

        skip_for_value();
        Value x;
        if (!parse_value(&x))
            return false;

        if (!a.empty()) {
            if (a.front().type() != x.type()) {
                add_error("type check failed");
                return false;
            }
        }

        a.push_back(std::move(x));
        skip_for_value();
        if (token().type() == TokenType::RBRACKET)
            break;
        if (token().type() == TokenType::COMMA)
            next_value();
    }

    if (!consume_for_value(TokenType::RBRACKET))
        return false;
    *v = std::move(a);
    return true;
}

bool Parser::parse_inline_table(Value* value)
{
    // For inline table, next is KEY, so use consume_for_key here.
    if (!consume_for_key(TokenType::LBRACE))
        return false;

    Value t((Table()));
    bool first = true;
    while (true) {
        if (token().type() == TokenType::RBRACE) {
            break;
        }

        if (!first) {
            if (token().type() != TokenType::COMMA) {
                add_error("inline table didn't have ',' for delimiter?");
                return false;
            }
            next_key();
        }
        first = false;

        std::string key;
        if (!parse_key(&key))
            return false;
        if (!consume_for_value(TokenType::EQUAL))
            return false;
        Value v;
        if (!parse_value(&v))
            return false;

        if (t.has(key)) {
            add_error("inline table has multiple same keys: key=" + key);
            return false;
        }

        t.set(key, v);
    }

    if (!consume_for_value(TokenType::RBRACE))
        return false;
    *value = std::move(t);
    return true;
}

} // namespace toml
