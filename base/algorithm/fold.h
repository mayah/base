#ifndef BASE_CONTAINERS_ALGORITHM_H_
#define BASE_CONTAINERS_ALGORITHM_H_

namespace base {

template<typename Iter, typename T, typename F>
T fold_left(Iter begin, Iter end, T init, F f)
{
    for (Iter it = begin; it != end; ++it) {
        init = f(init, *it);
    }
    return init;
}

} // namespace base

#endif // BASE_CONTAINERS_ALGORITHM_H_
