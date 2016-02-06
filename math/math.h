#ifndef MATH_MATH_H_
#define MATH_MATH_H_

namespace math {

int gcd(int a, int b);

// Exended euclidean algorithm
// When a, b are given, find x, y s.t. ax + by = gcd(a, b).
// Returns gcd(a, b).
int exgcd(int a, int b, int* x, int* y);


} // namespace math

#endif // MATH_MATH_H_
