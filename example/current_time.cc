#include <iostream>

#include "base/time/clock.h"
#include "base/time/time.h"

using namespace std;

int main()
{
    base::Time t = base::Clock::realClock()->now();
    time_t now = t.toTimeT();
    cout << ctime(&now) << endl;
}
