#include "base/concurrent/executor.h"

#include <gflags/gflags.h>
#include "third_party/glog/glog/logging.h"

DEFINE_int32(num_threads, 1, "The default number of threads");

using namespace std;

namespace base {

// static
unique_ptr<Executor> Executor::make_default(bool automatic_start)
{
    Executor* executor = new Executor(FLAGS_num_threads);
    if (automatic_start)
        executor->start();

    return unique_ptr<Executor>(executor);
}

Executor::Executor(int num_thread) :
    threads_(num_thread),
    should_stop_(false),
    has_started_(false)
{
}

Executor::~Executor()
{
    if (has_started_)
        stop();
}

void Executor::start()
{
    CHECK(!has_started_);
    has_started_ = true;

    for (size_t i = 0; i < threads_.size(); ++i) {
        threads_[i] = thread([this]() {
            run_worker_loop();
        });
    }
}

void Executor::stop()
{
    CHECK(has_started_);

    should_stop_ = true;
    cond_var_.notify_all();
    for (size_t i = 0; i < threads_.size(); ++i) {
        if (threads_[i].joinable()) {
            threads_[i].join();
        }
    }
}

void Executor::submit(Executor::Func f)
{
    CHECK(f) << "function should be callable";

    unique_lock<mutex> lock(mu_);
    tasks_.push_back(std::move(f));
    cond_var_.notify_one();
}

void Executor::run_worker_loop()
{
    while (true) {
        Func f = take();
        if (!f)
            break;

        f();
    }
}

Executor::Func Executor::take()
{
    unique_lock<mutex> lock(mu_);
    while (true) {
        if (!tasks_.empty())
            break;
        if (should_stop_)
            return Func();
        cond_var_.wait(lock);
    }

    Func f = std::move(tasks_.front());
    tasks_.pop_front();
    return f;
}

} // namespace base
