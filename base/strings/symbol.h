#ifndef BASE_STRINGS_SYMBOL_H_
#define BASE_STRINGS_SYMBOL_H_

#include <string>

namespace strings {

// Symbol is an intern-ed string.
// Symbol can be created via SymbolPool.
class Symbol {
public:
    Symbol() : impl_(nullptr) {}

    std::string to_string() const;

    const std::string* impl() const { return impl_; }

    friend bool operator==(const Symbol& lhs, const Symbol& rhs) { return lhs.impl_ == rhs.impl_; }
    friend bool operator!=(const Symbol& lhs, const Symbol& rhs) { return lhs.impl_ != rhs.impl_; }

    friend bool operator<(const Symbol& lhs, const Symbol& rhs);

private:
    friend class SymbolPool;

    explicit Symbol(const std::string* str) : impl_(str) {}

    const std::string* impl_;
};

inline std::string Symbol::to_string() const
{
    if (impl_ == nullptr)
        return std::string();
    return *impl_;
}

inline bool operator<(const Symbol& lhs, const Symbol& rhs)
{
    if (lhs.impl() == rhs.impl())
        return false;
    if (lhs.impl() == nullptr)
        return true;
    if (rhs.impl() == nullptr)
        return false;
    return *lhs.impl() < *rhs.impl();
}

} // namespace strings

#endif // BASE_STRINGS_SYMBOL_H_
