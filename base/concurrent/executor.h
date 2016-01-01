#ifndef BASE_CONCURRENT_EXECUTOR_H_
#define BASE_CONCURRENT_EXECUTOR_H_

#include <atomic>
#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

#include "base/macros.h"

namespace base {

// Executor is an implementation of thread pool.
// This implementation might have certain overhead. It's not intended to be used for
// a lot of micro tasks. Please submit coarse tasks.
class Executor {
public:
    typedef std::function<void (void)> Func;

    static std::unique_ptr<Executor> makeDefaultExecutor(bool automaticStart = true);

    explicit Executor(int numThread);
    ~Executor();

    void start();
    void stop();

    void submit(Func);

private:
    void runWorkerLoop();
    Func take();

    std::vector<std::thread> threads_;
    std::mutex mu_;
    std::condition_variable condVar_;
    std::atomic<bool> shouldStop_;
    std::deque<Func> tasks_;
    bool hasStarted_;

    DISALLOW_COPY_AND_ASSIGN(Executor);
};

} // namespace base

#endif // BASE_CONCURRENT_EXECUTOR_H_
