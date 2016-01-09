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

} // namespace vectors

#endif // BASE_CONTAINERS_VECTORS_H_
