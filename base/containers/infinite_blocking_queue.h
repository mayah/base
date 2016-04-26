#ifndef BASE_CONTAINERS_INFINITE_BLOCKING_QUEUE_H_
#define BASE_CONTAINERS_INFINITE_BLOCKING_QUEUE_H_

#include <cstdint>

#include "base/containers/blocking_queue.h"

namespace base {

// The same as base::BlockingQueue, however, no size limit
// (to be precise, size is size_t max.)
template<typename T>
class InfiniteBlockingQueue : public BlockingQueue<T> {
public:
    InfiniteBlockingQueue() : BlockingQueue<T>(SIZE_MAX) {}
};

} // namespace base

#endif // BASE_CONTAINERS_INFINITE_BLOCKING_QUEUE_H_
