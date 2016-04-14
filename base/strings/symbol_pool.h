#ifndef BASE_STRINGS_SYMBOL_POOL_H_
#define BASE_STRINGS_SYMBOL_POOL_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "base/strings/symbol.h"

namespace strings {

// SymbolPool generates a symbol.
// Symbol alives while SymbolPool is alive.
// This is not thread-safe.
class SymbolPool {
public:
    Symbol intern(std::string);

private:
    std::unordered_map<std::string, std::unique_ptr<std::string>> table_;
};

} // namespace strings

#endif // BASE_STRINGS_SYMBOL_POOL_H_
