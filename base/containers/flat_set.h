#ifndef BASE_CONTAINERS_FLAT_SET_H_
#define BASE_CONTAINERS_FLAT_SET_H_

#include <algorithm>
#include <utility>
#include <vector>

namespace base {

template<typename T>
class FlatSet {
public:
    // The underlying data should not be modified by the user.
    typedef typename std::vector<T>::const_iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    bool empty() const { return data_.empty(); }
    size_t size() const { return data_.size(); }

    iterator begin() { return data_.begin(); }
    const_iterator begin() const { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator end() const { return data_.end(); }

    // Inserts a new element. O(N)
    std::pair<iterator, bool> insert(const T& t);

    // Finds an element. O(log N)
    iterator find(const T& t) const;

private:
    std::vector<T> data_;
};

template<typename T>
std::pair<typename FlatSet<T>::iterator, bool> FlatSet<T>::insert(const T& t)
{
    auto it = std::lower_bound(data_.begin(), data_.end(), t);
    if (it == data_.end()) {
        data_.push_back(t);
        it = data_.end() - 1;
        return std::make_pair(it, true);
    }

    if (*it == t) {
        return std::make_pair(it, false);
    }

    it = data_.insert(it, t);
    return std::make_pair(it, true);
}

template<typename T>
typename FlatSet<T>::const_iterator FlatSet<T>::find(const T& t) const
{
    auto it = std::lower_bound(data_.begin(), data_.end(), t);
    if (*it == t)
        return it;
    return data_.end();
}

} // namespace base

#endif // BASE_CONTAINERS_FLAT_SET_H_
