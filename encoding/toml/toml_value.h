#ifndef ENCODING_TOML_TOML_VALUE_H_
#define ENCODING_TOML_TOML_VALUE_H_

#include <chrono>
#include <map>
#include <string>
#include <vector>

#include <glog/logging.h>

#include "encoding/toml/toml_util.h"

namespace toml {

class Value;
typedef std::chrono::system_clock::time_point Time;
typedef std::vector<Value> Array;
typedef std::map<std::string, Value> Table;

namespace internal {
template<typename T> struct call_traits_value {
    typedef T return_type;
};
template<typename T> struct call_traits_ref {
    typedef const T& return_type;
};
} // namespace internal

template<typename T> struct call_traits;
template<> struct call_traits<bool> : public internal::call_traits_value<bool> {};
template<> struct call_traits<int> : public internal::call_traits_value<int> {};
template<> struct call_traits<int64_t> : public internal::call_traits_value<int64_t> {};
template<> struct call_traits<double> : public internal::call_traits_value<double> {};
template<> struct call_traits<std::string> : public internal::call_traits_ref<std::string> {};
template<> struct call_traits<Time> : public internal::call_traits_ref<Time> {};
template<> struct call_traits<Array> : public internal::call_traits_ref<Array> {};
template<> struct call_traits<Table> : public internal::call_traits_ref<Table> {};

// A value is returned for std::vector<T>. Not reference.
// This is because a fresh vector is made.
template<typename T> struct call_traits<std::vector<T>> : public internal::call_traits_value<std::vector<T>> {};

class Value {
public:
    enum Type {
        NULL_TYPE,
        BOOL_TYPE,
        INT_TYPE,
        DOUBLE_TYPE,
        STRING_TYPE,
        TIME_TYPE,
        ARRAY_TYPE,
        TABLE_TYPE,
    };

    Value() : type_(NULL_TYPE), null_(nullptr) {}
    Value(bool v) : type_(BOOL_TYPE), bool_(v) {}
    Value(int v) : type_(INT_TYPE), int_(v) {}
    Value(int64_t v) : type_(INT_TYPE), int_(v) {}
    Value(double v) : type_(DOUBLE_TYPE), double_(v) {}
    Value(const std::string& v) : type_(STRING_TYPE), string_(new std::string(v)) {}
    Value(const char* v) : type_(STRING_TYPE), string_(new std::string(v)) {}
    Value(const Time& v) : type_(TIME_TYPE), time_(new Time(v)) {}
    Value(const Array& v) : type_(ARRAY_TYPE), array_(new Array(v)) {}
    Value(const Table& v) : type_(TABLE_TYPE), table_(new Table(v)) {}
    Value(std::string&& v) : type_(STRING_TYPE), string_(new std::string(std::move(v))) {}
    Value(Array&& v) : type_(ARRAY_TYPE), array_(new Array(std::move(v))) {}
    Value(Table&& v) : type_(TABLE_TYPE), table_(new Table(std::move(v))) {}

    Value(const Value& v);
    Value(Value&& v);
    Value& operator=(const Value& v);
    Value& operator=(Value&& v);

    // Someone might use a value like this:
    // toml::Value v = x->find("foo");
    // But this is wrong. Without this constructor,
    // value will be unexpectedly initialized with bool.
    Value(const void* v) = delete;
    ~Value();

    size_t size() const;
    bool empty() const;
    Type type() const { return type_; }

    bool valid() const { return type_ != NULL_TYPE; }
    template<typename T> bool is() const;
    template<typename T> typename call_traits<T>::return_type as() const;

    // Returns true if the value is int or double.
    bool is_number() const;
    // Returns number. Convert to double.
    double as_number() const;

    // For table value
    template<typename T> typename call_traits<T>::return_type get(const std::string&) const;
    Value* set(const std::string& key, const Value& v);
    const Value* find(const std::string& key) const;
    Value* find(const std::string& key);
    bool has(const std::string& key) const { return find(key) != nullptr; }
    bool erase(const std::string& key);

    // Merge table. Returns true if succeeded. Otherwise, |this| might be corrupted.
    bool merge(const Value&);

    // find_child finds a value with having |key|. We don't have |key|.
    Value* find_child(const std::string& key);
    const Value* find_child(const std::string& key) const;
    Value* set_child(const std::string& key, const Value& v);
    bool erase_child(const std::string& key);

    // For array value
    template<typename T> typename call_traits<T>::return_type get(size_t index) const;
    const Value* find(size_t index) const;
    Value* find(size_t index);
    Value* push(const Value& v);

    // Writer.
    void write(std::ostream*, const std::string& keyPrefix = std::string()) const;
    friend std::ostream& operator<<(std::ostream&, const Value&);

    Value& operator[](const std::string& key);
    friend bool operator==(const Value& lhs, const Value& rhs);
    friend bool operator!=(const Value& lhs, const Value& rhs) { return !(lhs == rhs); }

private:
    static const char* type_to_string(Type);

    template<typename T> void assure_type() const;
    Value* ensure_value(const std::string& key);

    template<typename T> struct ValueConverter;

    Type type_;
    union {
        void* null_;
        bool bool_;
        int64_t int_;
        double double_;
        std::string* string_;
        Time* time_;
        Array* array_;
        Table* table_;
    };

    template<typename T> friend struct ValueConverter;
};

template<> struct Value::ValueConverter<bool>
{
    bool is(const Value& v) { return v.type() == Value::BOOL_TYPE; }
    bool to(const Value& v) { v.assure_type<bool>(); return v.bool_; }

};
template<> struct Value::ValueConverter<int64_t>
{
    bool is(const Value& v) { return v.type() == Value::INT_TYPE; }
    int64_t to(const Value& v) { v.assure_type<int64_t>(); return v.int_; }
};
template<> struct Value::ValueConverter<int>
{
    bool is(const Value& v) { return v.type() == Value::INT_TYPE; }
    int to(const Value& v) { v.assure_type<int>(); return static_cast<int>(v.int_); }
};
template<> struct Value::ValueConverter<double>
{
    bool is(const Value& v) { return v.type() == Value::DOUBLE_TYPE; }
    double to(const Value& v) { v.assure_type<double>(); return v.double_; }
};
template<> struct Value::ValueConverter<std::string>
{
    bool is(const Value& v) { return v.type() == Value::STRING_TYPE; }
    const std::string& to(const Value& v) { v.assure_type<std::string>(); return *v.string_; }
};
template<> struct Value::ValueConverter<Time>
{
    bool is(const Value& v) { return v.type() == Value::TIME_TYPE; }
    const Time& to(const Value& v) { v.assure_type<Time>(); return *v.time_; }
};
template<> struct Value::ValueConverter<Array>
{
    bool is(const Value& v) { return v.type() == Value::ARRAY_TYPE; }
    const Array& to(const Value& v) { v.assure_type<Array>(); return *v.array_; }
};
template<> struct Value::ValueConverter<Table>
{
    bool is(const Value& v) { return v.type() == Value::TABLE_TYPE; }
    const Table& to(const Value& v) { v.assure_type<Table>(); return *v.table_; }
};

template<typename T>
struct Value::ValueConverter<std::vector<T>>
{
    bool is(const Value& v)
    {
        if (v.type() != Value::ARRAY_TYPE)
            return false;
        const Array& array = v.as<Array>();
        if (array.empty())
            return true;
        return array.front().is<T>();
    }

    std::vector<T> to(const Value& v)
    {
        const Array& array = v.as<Array>();
        if (array.empty())
            return std::vector<T>();
        array.front().assure_type<T>();

        std::vector<T> result;
        for (const auto& element : array) {
            result.push_back(element.as<T>());
        }

        return result;
    }
};

namespace internal {
template<typename T> inline const char* type_name();
template<> inline const char* type_name<bool>() { return "bool"; }
template<> inline const char* type_name<int>() { return "int"; }
template<> inline const char* type_name<int64_t>() { return "int64_t"; }
template<> inline const char* type_name<double>() { return "double"; }
template<> inline const char* type_name<std::string>() { return "string"; }
template<> inline const char* type_name<toml::Time>() { return "time"; }
template<> inline const char* type_name<toml::Array>() { return "array"; }
template<> inline const char* type_name<toml::Table>() { return "table"; }
} // namespace internal

template<typename T>
void Value::assure_type() const
{
    CHECK(is<T>()) << "type error: this value is " << type_to_string(type_)
                   << " but " << internal::type_name<T>() << " was requested";
}

template<typename T>
bool Value::is() const
{
    return ValueConverter<T>().is(*this);
}

template<typename T>
typename call_traits<T>::return_type Value::as() const
{
    return ValueConverter<T>().to(*this);
}

template<typename T>
typename call_traits<T>::return_type Value::get(const std::string& key) const
{
    CHECK(is<Table>()) << "type must be table to do get(key).";

    const Value* obj = find(key);
    CHECK(obj) << "key " << key << " was not found.";

    return obj->as<T>();
}

template<typename T>
typename call_traits<T>::return_type Value::get(size_t index) const
{
    CHECK(is<Array>()) << "type must be array to do get(index).";
    CHECK(index < array_->size()) << "index out of bound";

    return (*array_)[index].as<T>();
}


} // namespace toml

#endif // ENCODING_TOML_TOML_VALUE_H_
