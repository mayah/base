#ifndef MATH_SIGMOID_H_
#define MATH_SIGMOID_H_

#include <cmath>

namespace math {

inline float sigmoid(float x, float a)
{
    return 1 / (1 + std::exp(-a * x));
}

inline double sigmoid(double x, double a)
{
    return 1 / (1 + std::exp(-a * x));
}

inline float d_sigmoid(float x, float a)
{
    return a * sigmoid(x, a) * (1 - sigmoid(x, a));
}

inline double d_sigmoid(double x, double a)
{
    return a * sigmoid(x, a) * (1 - sigmoid(x, a));
}

} // namespace math

#endif // MATH_SIGMOID_H_
