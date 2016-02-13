#include "encoding/toml/toml_parser.h"

namespace toml {

void Parser::skipForKey()
{
    while (token().type() == TokenType::END_OF_LINE)
        nextKey();
}

void Parser::skipForValue()
{
    while (token().type() == TokenType::END_OF_LINE)
        nextValue();
}

bool Parser::consumeForKey(TokenType type)
{
    if (token().type() == type) {
        nextKey();
        return true;
    }

    return false;
}

bool Parser::consumeForValue(TokenType type)
{
    if (token().type() == type) {
        nextValue();
        return true;
    }

    return false;
}

bool Parser::consumeEOLorEOFForKey()
{
    if (token().type() == TokenType::END_OF_LINE || token().type() == TokenType::END_OF_FILE) {
        nextKey();
        return true;
    }

    return false;
}

void Parser::addError(const std::string& reason)
{
    if (!errorReason_.empty())
        return;

    std::stringstream ss;
    ss << "Error: line " << lexer_.lineNo() << ": " << reason;
    errorReason_ = ss.str();
}

const std::string& Parser::errorReason()
{
    return errorReason_;
}

Value Parser::parse()
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

Value* Parser::parseGroupKey(Value* root)
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

bool Parser::parseKeyValue(Value* current)
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

bool Parser::parseKey(std::string* key)
{
    key->clear();

    if (token().type() == TokenType::IDENT || token().type() == TokenType::STRING) {
        *key = token().strValue();
        nextValue();
        return true;
    }

    return false;
}

bool Parser::parseValue(Value* v)
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

bool Parser::parseBool(Value* v)
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

bool Parser::parseArray(Value* v)
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

bool Parser::parseInlineTable(Value* value)
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

} // namespace toml
