#include "base/strings/symbol_pool.h"

namespace strings {

Symbol SymbolPool::intern(std::string str)
{
    auto it = table_.find(str);
    if (it != table_.end())
        return Symbol(it->second.get());

    auto ptr = new std::string(str);
    std::unique_ptr<std::string> value(ptr);
    table_.emplace(std::move(str), std::move(value));
    return Symbol(ptr);
}

} // namespace strings
