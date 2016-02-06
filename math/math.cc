#include "math/math.h"

namespace math {

int gcd(int a, int b)
{
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }

    return a;
}

int exgcd(int a, int b, int* x, int* y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int d = exgcd(b, a % b, y, x);
    *y -= a / b * *x;
    return d;
}

} // namespace gcd
