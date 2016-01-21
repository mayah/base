#ifndef BASE_CONTAINERS_REVERSE_RANGE_H_
#define BASE_CONTAINERS_REVERSE_RANGE_H_

#include <cstddef>
#include <iterator>

namespace base {
namespace internal {

// Internal adapter class for implementing base::Reversed.
template<typename T>
class ReversedAdapter {
public:
    using Iterator = decltype(static_cast<T*>(nullptr)->rbegin());

    explicit ReversedAdapter(T& t) : t_(t) {}
    ReversedAdapter(const ReversedAdapter& ra) : t_(ra.t_) {}

    Iterator begin() const { return t_.rbegin(); }
    Iterator end() const { return t_.rend(); }

private:
    T& t_;
};

template <typename T, size_t N>
class ReversedAdapter<T[N]> {
public:
    using Iterator = std::reverse_iterator<T*>;

    explicit ReversedAdapter(T (&t)[N]) : t_(t) {}
    ReversedAdapter(const ReversedAdapter& ra) : t_(ra.t_) {}

    Iterator begin() const { return Iterator(&t_[N]); }
    Iterator end() const { return Iterator(&t_[0]); }

private:
    T (&t_)[N];
};

}  // namespace internal

// reverse_range can be used like the following.
// for (auto& v : base::reverse_range(vs)) {
//     ...
// }
template <typename T>
internal::ReversedAdapter<T> reverse_range(T& t) {
    return internal::ReversedAdapter<T>(t);
}

} // namespace base

#endif // BASE_CONTAINERS_REVERSE_RANGE_H_
