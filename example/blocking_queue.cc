#include <iostream>

#include "base/containers/blocking_queue.h"

int main(int argc, char* argv[])
{
    base::BlockingQueue<int> t(10);
    t.push(1);
    t.push(2);
    t.push(3);

    int v;
    if (t.take_with_timeout(std::chrono::seconds(3), &v)) {
        std::cout << v << std::endl;
    } else {
        std::cout << "failed to take" << std::endl;
    }

    if (t.take_with_timeout(std::chrono::seconds(3), &v)) {
        std::cout << v << std::endl;
    } else {
        std::cout << "failed to take" << std::endl;
    }

    if (t.take_with_timeout(std::chrono::seconds(3), &v)) {
        std::cout << v << std::endl;
    } else {
        std::cout << "failed to take" << std::endl;
    }

    if (t.take_with_timeout(std::chrono::seconds(3), &v)) {
        std::cout << v << std::endl;
    } else {
        std::cout << "failed to take" << std::endl;
    }

    return 0;
}
