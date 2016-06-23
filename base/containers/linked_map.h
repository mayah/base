#ifndef BASE_CONTAINERS_LINKED_MAP_H_
#define BASE_CONTAINERS_LINKED_MAP_H_

#include <list>
#include <map>

namespace base {

template<typename K, typename V>
class LinkedMap {
public:
    typedef typename std::list<std::pair<const K, V>> cdata_type;

    typedef typename cdata_type::iterator iterator;
    typedef typename cdata_type::const_iterator const_iterator;

    bool empty() const { return cdata_.empty(); }
    size_t size() const { return cdata_.size(); }

    iterator find(const K& key);
    const_iterator find(const K& key) const;

    std::pair<iterator, bool> insert(const std::pair<const K, V>& entry);

    iterator begin() { return cdata_.begin(); }
    const_iterator begin() const { return cdata_.begin(); }
    iterator end() { return cdata_.end(); }
    const_iterator end() const { return cdata_.end(); }

private:
    std::list<std::pair<const K, V>> cdata_;
    std::map<K, iterator> index_;
};

template<typename K, typename V>
typename LinkedMap<K, V>::iterator LinkedMap<K, V>::find(const K& key)
{
    auto it = index_.find(key);
    if (it == index_.end()) {
        return cdata_.end();
    }

    return it->second;
}

template<typename K, typename V>
typename LinkedMap<K, V>::const_iterator LinkedMap<K, V>::find(const K& key) const
{
    auto it = index_.find(key);
    if (it == index_.end()) {
        return cdata_.end();
    }

    return it->second;
}

template<typename K, typename V>
std::pair<typename LinkedMap<K, V>::iterator, bool> LinkedMap<K, V>::insert(const std::pair<const K, V>& entry)
{
    {
        auto it = index_.find(entry.first);
        if (it != index_.end()) {
            return std::make_pair(it->second, false);
        }
    }

    cdata_.push_back(entry);
    auto jt = cdata_.end();
    --jt;
    index_.insert(std::make_pair(entry.first, jt));

    return std::make_pair(jt, true);
}

} // namespace base

#endif // BASE_CONTAINERS_LINKED_MAP_H_
