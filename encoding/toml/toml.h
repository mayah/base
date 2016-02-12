#ifndef ENCODING_TOML_TOML_H_
#define ENCODING_TOML_TOML_H_

#include <chrono>
#include <string>
#include <map>
#include <vector>

namespace toml {

// ----------------------------------------------------------------------
// Declarations

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
    bool isNumber() const;
    // Returns number. Convert to double.
    double asNumber() const;

    // For table value
    template<typename T> typename call_traits<T>::return_type get(const std::string&) const;
    Value* set(const std::string& key, const Value& v);
    const Value* find(const std::string& key) const;
    Value* find(const std::string& key);
    bool has(const std::string& key) const { return find(key) != nullptr; }
    bool erase(const std::string& key);

    // Merge table. Returns true if succeeded. Otherwise, |this| might be corrupted.
    bool merge(const Value&);

    // findChild finds a value with having |key|. We don't have |key|.
    Value* findChild(const std::string& key);
    const Value* findChild(const std::string& key) const;
    Value* setChild(const std::string& key, const Value& v);
    bool eraseChild(const std::string& key);

    // For array value
    template<typename T> typename call_traits<T>::return_type get(size_t index) const;
    const Value* find(size_t index) const;
    Value* find(size_t index);
    Value* push(const Value& v);

    // Writer.
    void write(std::ostream*, const std::string& keyPrefix = std::string()) const;
    friend std::ostream& operator<<(std::ostream&, const Value&);

    // Deprecated because of name confusion.
    // TODO(mayah): Mark as deprecated.
    Value* findSingle(const std::string& key) { return findChild(key); }
    const Value* findSingle(const std::string& key) const { return findChild(key); }
    Value* setSingle(const std::string& key, const Value& v) { return setChild(key, v); }

private:
    static const char* typeToString(Type);

    template<typename T> void assureType() const;
    Value* ensureValue(const std::string& key);

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

} // namespace toml

#endif // ENCODING_TOML_TOML_H_
