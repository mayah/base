#include <iostream>

#include "base/time/clock.h"
#include "base/time/scoped_time.h"
#include "base/time/time.h"

using namespace std;

int fib(int n)
{
    if (n <= 2)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

void f()
{
    double d;
    {
        base::ScopedTime st(&d);
        cout << fib(42) << endl;
    }
    cout << d << endl;
}

int main()
{
    base::Time t = base::Clock::real_clock()->now();
    time_t now = t.to_time_t();
    cout << ctime(&now) << endl;

    f();
    return 0;
}
