#ifndef MATH_GAUSE_H_
#define MATH_GAUSE_H_

#include <vector>

namespace math {

// Solve Ax = b
bool gauss(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double>* x);

} // namespace math

#endif // MATH_GAUSE_H_
