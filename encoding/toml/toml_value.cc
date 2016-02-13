#include "encoding/toml/toml_value.h"

#include <cassert>

#include "encoding/toml/toml.h"

namespace toml {

const char* Value::typeToString(Value::Type type)
{
    switch (type) {
    case NULL_TYPE:   return "null";
    case BOOL_TYPE:   return "bool";
    case INT_TYPE:    return "int";
    case DOUBLE_TYPE: return "double";
    case STRING_TYPE: return "string";
    case TIME_TYPE:   return "time";
    case ARRAY_TYPE:  return "array";
    case TABLE_TYPE:  return "table";
    default:          return "unknown";
    }
}

Value::Value(const Value& v) :
    type_(v.type_)
{
    switch (v.type_) {
    case NULL_TYPE: null_ = v.null_; break;
    case BOOL_TYPE: bool_ = v.bool_; break;
    case INT_TYPE: int_ = v.int_; break;
    case DOUBLE_TYPE: double_ = v.double_; break;
    case STRING_TYPE: string_ = new std::string(*v.string_); break;
    case TIME_TYPE: time_ = new Time(*v.time_); break;
    case ARRAY_TYPE: array_ = new Array(*v.array_); break;
    case TABLE_TYPE: table_ = new Table(*v.table_); break;
    default:
        assert(false);
        type_ = NULL_TYPE;
        null_ = nullptr;
    }
}

Value::Value(Value&& v) :
    type_(v.type_)
{
    switch (v.type_) {
    case NULL_TYPE: null_ = v.null_; break;
    case BOOL_TYPE: bool_ = v.bool_; break;
    case INT_TYPE: int_ = v.int_; break;
    case DOUBLE_TYPE: double_ = v.double_; break;
    case STRING_TYPE: string_ = v.string_; break;
    case TIME_TYPE: time_ = v.time_; break;
    case ARRAY_TYPE: array_ = v.array_; break;
    case TABLE_TYPE: table_ = v.table_; break;
    default:
        assert(false);
        type_ = NULL_TYPE;
        null_ = nullptr;
    }

    v.type_ = NULL_TYPE;
    v.null_ = nullptr;
}

Value& Value::operator=(const Value& v)
{
    if (this == &v)
        return *this;

    this->~Value();

    type_ = v.type_;
    switch (v.type_) {
    case NULL_TYPE: null_ = v.null_; break;
    case BOOL_TYPE: bool_ = v.bool_; break;
    case INT_TYPE: int_ = v.int_; break;
    case DOUBLE_TYPE: double_ = v.double_; break;
    case STRING_TYPE: string_ = new std::string(*v.string_); break;
    case TIME_TYPE: time_ = new Time(*v.time_); break;
    case ARRAY_TYPE: array_ = new Array(*v.array_); break;
    case TABLE_TYPE: table_ = new Table(*v.table_); break;
    default:
        assert(false);
        type_ = NULL_TYPE;
        null_ = nullptr;
    }

    return *this;
}

Value& Value::operator=(Value&& v)
{
    if (this == &v)
        return *this;

    this->~Value();

    type_ = v.type_;
    switch (v.type_) {
    case NULL_TYPE: null_ = v.null_; break;
    case BOOL_TYPE: bool_ = v.bool_; break;
    case INT_TYPE: int_ = v.int_; break;
    case DOUBLE_TYPE: double_ = v.double_; break;
    case STRING_TYPE: string_ = v.string_; break;
    case TIME_TYPE: time_ = v.time_; break;
    case ARRAY_TYPE: array_ = v.array_; break;
    case TABLE_TYPE: table_ = v.table_; break;
    default:
        assert(false);
        type_ = NULL_TYPE;
        null_ = nullptr;
    }

    v.type_ = NULL_TYPE;
    v.null_ = nullptr;
    return *this;
}

Value::~Value()
{
    switch (type_) {
    case STRING_TYPE:
        delete string_;
        break;
    case TIME_TYPE:
        delete time_;
        break;
    case ARRAY_TYPE:
        delete array_;
        break;
    case TABLE_TYPE:
        delete table_;
        break;
    default:
        break;
    }
}

size_t Value::size() const
{
    switch (type_) {
    case NULL_TYPE:
        return 0;
    case ARRAY_TYPE:
        return array_->size();
    case TABLE_TYPE:
        return table_->size();
    default:
        return 1;
    }
}

bool Value::empty() const
{
    return size() == 0;
}

bool Value::isNumber() const
{
    return is<int>() || is<double>();
}

double Value::asNumber() const
{
    if (is<int>())
        return as<int>();
    if (is<double>())
        return as<double>();

    failwith("type error: this value is ", typeToString(type_), " but number is requested");
    return 0.0;
}

void Value::write(std::ostream* os, const std::string& keyPrefix) const
{
    switch (type_) {
    case NULL_TYPE:
        failwith("null type value is not a valid value");
        break;
    case BOOL_TYPE:
        (*os) << (bool_ ? "true" : "false");
        break;
    case INT_TYPE:
        (*os) << int_;
        break;
    case DOUBLE_TYPE: {
        (*os) << std::fixed << std::showpoint << double_;
        break;
    }
    case STRING_TYPE:
        (*os) << '"' << escapeString(*string_) << '"';
        break;
    case TIME_TYPE: {
        time_t tt = std::chrono::system_clock::to_time_t(*time_);
        std::tm t;
        gmtime_r(&tt, &t);
        char buf[256];
        sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02dZ", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
        (*os) << buf;
        break;
    }
    case ARRAY_TYPE:
        (*os) << '[';
        for (size_t i = 0; i < array_->size(); ++i) {
            if (i)
                (*os) << ", ";
            (*array_)[i].write(os, keyPrefix);
        }
        (*os) << ']';
        break;
    case TABLE_TYPE:
        for (const auto& kv : *table_) {
            if (kv.second.is<Table>())
                continue;
            if (kv.second.is<Array>() && kv.second.size() > 0 && kv.second.find(0)->is<Table>())
                continue;
            (*os) << kv.first << " = ";
            kv.second.write(os, keyPrefix);
            (*os) << '\n';
        }
        for (const auto& kv : *table_) {
            if (kv.second.is<Table>()) {
                std::string key(keyPrefix);
                if (!keyPrefix.empty())
                    key += ".";
                key += kv.first;
                (*os) << "\n[" << key << "]\n";
                kv.second.write(os, key);
            }
            if (kv.second.is<Array>() && kv.second.size() > 0 && kv.second.find(0)->is<Table>()) {
                std::string key(keyPrefix);
                if (!keyPrefix.empty())
                    key += ".";
                key += kv.first;
                for (const auto& v : kv.second.as<Array>()) {
                    (*os) << "\n[[" << key << "]]\n";
                    v.write(os, key);
                }
            }
        }
        break;
    default:
        failwith("writing unknown type");
        break;
    }
}

// static
std::ostream& operator<<(std::ostream& os, const toml::Value& v)
{
    v.write(&os);
    return os;
}

const Value* Value::find(const std::string& key) const
{
    if (!is<Table>())
        return nullptr;

    std::istringstream ss(key);
    Lexer lexer(ss);

    const Value* current = this;
    while (true) {
        Token t = lexer.next_key_token();
        if (!(t.type() == TokenType::IDENT || t.type() == TokenType::STRING))
            return nullptr;

        std::string part = t.str_value();
        t = lexer.next_key_token();
        if (t.type() == TokenType::DOT) {
            current = current->find_child(part);
            if (!current || !current->is<Table>())
                return nullptr;
        } else if (t.type() == TokenType::END_OF_FILE) {
            return current->find_child(part);
        } else {
            return nullptr;
        }
    }
}

Value* Value::find(const std::string& key)
{
    return const_cast<Value*>(const_cast<const Value*>(this)->find(key));
}

bool Value::merge(const toml::Value& v)
{
    if (this == &v)
        return true;
    if (!is<Table>() || !v.is<Table>())
        return false;

    for (const auto& kv : *v.table_) {
        if (Value* tmp = find(kv.first)) {
            // If both are table, we merge them.
            if (tmp->is<Table>() && kv.second.is<Table>()) {
                if (!tmp->merge(kv.second))
                    return false;
            } else {
                set_child(kv.first, kv.second);
            }
        } else {
            set_child(kv.first, kv.second);
        }
    }

    return true;
}

Value* Value::set(const std::string& key, const Value& v)
{
    Value* result = ensureValue(key);
    *result = v;
    return result;
}

Value* Value::set_child(const std::string& key, const Value& v)
{
    if (!valid())
        *this = Value((Table()));

    if (!is<Table>())
        failwith("type must be table to do set(key, v).");

    (*table_)[key] = v;
    return &(*table_)[key];
}

bool Value::erase(const std::string& key)
{
    if (!is<Table>())
        return false;

    std::istringstream ss(key);
    Lexer lexer(ss);

    Value* current = this;
    while (true) {
        Token t = lexer.next_key_token();
        if (!(t.type() == TokenType::IDENT || t.type() == TokenType::STRING))
            return false;

        std::string part = t.str_value();
        t = lexer.next_key_token();
        if (t.type() == TokenType::DOT) {
            current = current->find_child(part);
            if (!current || !current->is<Table>())
                return false;
        } else if (t.type() == TokenType::END_OF_FILE) {
            return current->erase_child(part);
        } else {
            return false;
        }
    }
}

bool Value::erase_child(const std::string& key)
{
    if (!is<Table>())
        failwith("type must be table to do erase(key).");

    return table_->erase(key) > 0;
}

const Value* Value::find(size_t index) const
{
    if (!is<Array>())
        return nullptr;
    if (index < array_->size())
        return &(*array_)[index];
    return nullptr;
}

Value* Value::find(size_t index)
{
    return const_cast<Value*>(const_cast<const Value*>(this)->find(index));
}

Value* Value::push(const Value& v)
{
    if (!valid())
        *this = Value((Array()));
    else if (!is<Array>())
        failwith("type must be array to do push(Value).");

    array_->push_back(v);
    return &array_->back();
}

Value* Value::ensureValue(const std::string& key)
{
    if (!valid())
        *this = Value((Table()));
    if (!is<Table>()) {
        failwith("encountered non table value");
        return nullptr;
    }

    std::istringstream ss(key);
    Lexer lexer(ss);

    Value* current = this;
    while (true) {
        Token t = lexer.next_key_token();
        if (!(t.type() == TokenType::IDENT || t.type() == TokenType::STRING)) {
            failwith("invalid key");
            return nullptr;
        }

        std::string part = t.str_value();
        t = lexer.next_key_token();
        if (t.type() == TokenType::DOT) {
            if (Value* candidate = current->find_child(part)) {
                if (!candidate->is<Table>())
                    failwith("encountered non table value");
                current = candidate;
            } else {
                current = current->set_child(part, Table());
            }
        } else if (t.type() == TokenType::END_OF_FILE) {
            if (Value* v = current->find_child(part))
                return v;
            return current->set_child(part, Value());
        } else {
            failwith("invalid key");
            return nullptr;
        }
    }
}

Value* Value::find_child(const std::string& key)
{
    assert(is<Table>());

    auto it = table_->find(key);
    if (it == table_->end())
        return nullptr;

    return &it->second;
}

const Value* Value::find_child(const std::string& key) const
{
    assert(is<Table>());

    auto it = table_->find(key);
    if (it == table_->end())
        return nullptr;

    return &it->second;
}

} // namespace toml
