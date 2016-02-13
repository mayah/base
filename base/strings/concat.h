#ifndef STRINGS_CONCAT_H_
#define STRINGS_CONCAT_H_

#include <sstream>
#include <string>
#include <utility>

namespace strings {

namespace internal {

inline std::string concatImpl(std::stringstream& ss)
{
    return ss.str();
}

template<typename T, typename... Args>
std::string concatImpl(std::stringstream& ss, T&& t, Args&&... args)
{
    ss << std::forward<T>(t);
    return concatImpl(ss, std::forward<Args>(args)...);
}

} // namespace internal

template<typename... Args>
inline std::string concat(Args&&... args)
{
    std::stringstream ss;
    return internal::concatImpl(ss, std::forward<Args>(args)...);
}

} // namespace strings

#endif // STRINGS_FORMAT_H_
