#ifndef BASE_CONTAINERS_ASSOC_MAP_H_
#define BASE_CONTAINERS_ASSOC_MAP_H_

#include <cstddef>
#include <vector>
#include <utility>

namespace base {

// AssocMap is a simple array based map.
template<typename K, typename V>
class AssocMap {
public:
    typedef typename std::vector<std::pair<K, V>> data_type;
    typedef typename std::vector<std::pair<const K, V>> cdata_type;

    typedef typename cdata_type::iterator iterator;
    typedef typename cdata_type::const_iterator const_iterator;

    AssocMap() : data_() {}
    ~AssocMap() { data_.~data_type(); }

    bool empty() const { return data_.empty(); }
    std::size_t size() const { return data_.size(); }

    iterator find(const K& key);
    const_iterator find(const K& key) const;

    std::pair<iterator, bool> insert(const std::pair<K, V>& entry);

private:
    union {
        std::vector<std::pair<K, V>> data_;
        std::vector<std::pair<const K, V>> cdata_;
    };
};

template<typename K, typename V>
typename AssocMap<K, V>::iterator AssocMap<K, V>::find(const K& key)
{
    for (auto it = cdata_.begin(); it != cdata_.end(); ++it) {
        if (key == it->first)
            return it;
    }

    return cdata_.end();
}

template<typename K, typename V>
typename AssocMap<K, V>::const_iterator AssocMap<K, V>::find(const K& key) const
{
    for (auto it = cdata_.begin(); it != cdata_.end(); ++it) {
        if (key == it->first)
            return it;
    }

    return cdata_.end();
}

template<typename K, typename V>
std::pair<typename AssocMap<K, V>::iterator, bool> AssocMap<K, V>::insert(const std::pair<K, V>& entry)
{
    for (auto it = cdata_.begin(); it != cdata_.end(); ++it) {
        if (entry.first == it->first) {
            return std::make_pair(it, false);
        }
    }

    cdata_.push_back(std::make_pair(entry.first, entry.second));
    return std::make_pair(cdata_.end() - 1, true);
}

} // namespace base

#endif // BASE_CONTAINERS_ASSOC_MAP_H_
