#include "base/time/lap_timer.h"

#include <thread>
#include <iostream>

int main()
{
    base::LapTimer timer;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    timer.lap("slept 1");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    timer.lap("slept 2");

    for (const auto& lap : timer.laps()) {
        std::cout << lap.first.to_localtime_string()
                  << " -> " << lap.second
                  << std::endl;
    }
    return 0;
}
