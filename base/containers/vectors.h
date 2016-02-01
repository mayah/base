#ifndef BASE_CONTAINERS_VECTORS_H_
#define BASE_CONTAINERS_VECTORS_H_

// vectors contains vector helper functions.

#include <cstddef>
#include <vector>

namespace vectors {

// init creates a fresh std::vector<T> whose i-th value is fn(i).
template<typename T, typename F>
std::vector<T> init(size_t size, F fn)
{
    std::vector<T> t;
    t.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        t.push_back(fn(i));
    }
    return t;
}

// range() creates a new vector that starts with |begin|.
std::vector<int> range(int begin, int end);

template<typename T, typename F>
auto map(const std::vector<T>& vs, F f) -> std::vector<decltype(f(vs[0]))>
{
    using R = decltype(f(T()));
    std::vector<R> results;
    results.reserve(vs.size());
    for (const auto& v : vs) {
        results.push_back(f(v));
    }

    return results;
}

} // namespace vectors

#endif // BASE_CONTAINERS_VECTORS_H_
