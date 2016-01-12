#ifndef BASE_CONTAINERS_VECTORS_IO_H_
#define BASE_CONTAINERS_VECTORS_IO_H_

#include <ostream>
#include <vector>

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& vs)
{
    for (size_t i = 0; i < vs.size(); ++i) {
        if (i > 0)
            os << ' ';
        os << vs[i];
    }

    return os;
}

#endif // BASE_CONTAINERS_VECTORS_IO_H_
