#ifndef BASE_BITS_COUNT_H_
#define BASE_BITS_COUNT_H_

#include <cstdint>

namespace base {

inline int popcount32(std::uint32_t x)
{
    return __builtin_popcount(x);
}

inline int popcount64(std::uint64_t x)
{
    return __builtin_popcountll(x);
}

// Returns the number of leading/trailing 0-bits in x, starting at the MSB/LSB.
// If x is 0, the result is undefined.
// e.g. x = 00101000 10010101 10111000 01000000, CLZ(x) = 2 and CTZ = 6.
//          ^^                           ^^^^^^
//          CLZ counts here.             CTZ counts here.

inline int clz32(std::uint32_t x)
{
    return __builtin_clz(x);
}

inline int clz64(std::uint64_t x)
{
    return __builtin_clzll(x);
}

inline int ctz32(std::uint32_t x)
{
    return __builtin_ctz(x);
}

inline int ctz64(std::uint64_t x)
{
    return __builtin_ctzll(x);
}

} // namespace base

#endif // BASE_BITS_POPCOUNT_H_
