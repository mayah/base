#include <iostream>

#include "base/time/clock.h"
#include "base/time/time.h"

using namespace std;

int main()
{
    base::Time t = base::Clock::real_clock()->now();
    time_t now = t.to_time_t();
    cout << ctime(&now) << endl;
}
