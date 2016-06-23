#ifndef BASE_CONTAINERS_FLAT_MAP_H_
#define BASE_CONTAINERS_FLAT_MAP_H_

#include <algorithm>
#include <utility>
#include <vector>

namespace base {

// FlatMap is just a sorted std::vector<std::pair<const K, V>>.
template<typename K, typename V>
class FlatMap {
public:
    typedef typename std::vector<std::pair<K, V>> data_type;
    typedef typename std::vector<std::pair<const K, V>> cdata_type;

    typedef typename cdata_type::iterator iterator;
    typedef typename cdata_type::const_iterator const_iterator;

    FlatMap() : data_() {}
    ~FlatMap() { data_.~data_type(); }

    bool empty() const { return cdata_.empty(); }
    size_t size() const { return cdata_.size(); }

    iterator begin() { return cdata_.begin(); }
    const_iterator begin() const { return cdata_.begin(); }
    const_iterator cbegin() const { return cdata_.cbegin(); }
    iterator end() { return cdata_.end(); }
    const_iterator end() const { return cdata_.end(); }
    const_iterator cend() const{ return cdata_.cend(); }

    iterator find(const K& key);
    const_iterator find(const K& key) const;

    std::pair<iterator, bool> insert(const std::pair<const K, V>& entry);

private:
    struct KeyOnlyComparator {
        bool operator()(const std::pair<const K, V>& lhs, const std::pair<const K, V>& rhs) const {
            return lhs.first < rhs.first;
        }
        bool operator()(const std::pair<const K, V>& lhs, const K& rhs) const {
            return lhs.first < rhs;
        }
    };

    union {
        std::vector<std::pair<K, V>> data_;
        std::vector<std::pair<const K, V>> cdata_;
    };
};

template<typename K, typename V>
typename FlatMap<K, V>::iterator FlatMap<K, V>::find(const K& key)
{
    auto it = std::lower_bound(data_.begin(), data_.end(), key, KeyOnlyComparator());
    if (it != data_.end() && it->first == key) {
        size_t idx = it - data_.begin();
        return cdata_.begin() + idx;

    }

    return cdata_.end();
}

template<typename K, typename V>
typename FlatMap<K, V>::const_iterator FlatMap<K, V>::find(const K& key) const
{
    auto it = std::lower_bound(data_.begin(), data_.end(), key, KeyOnlyComparator());
    if (it != data_.end() && it->first == key) {
        size_t idx = it - data_.begin();
        return cdata_.begin() + idx;

    }

    return cdata_.end();
}

template<typename K, typename V>
std::pair<typename FlatMap<K, V>::iterator, bool> FlatMap<K, V>::insert(const std::pair<const K, V>& entry)
{
    auto it = std::lower_bound(data_.begin(), data_.end(), entry, KeyOnlyComparator());
    size_t idx = it - data_.begin();

    if (it != data_.end() && it->first == entry.first) {
        return make_pair(cdata_.begin() + idx, false);
    }

    auto jt = data_.insert(it, entry);
    size_t jdx = jt - data_.begin();
    return std::make_pair(cdata_.begin() + jdx, true);
}

} // namespace base

#endif // BASE_CONTAINERS_FLAT_MAP_H_
