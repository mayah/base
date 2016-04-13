#ifndef MATH_KNAPSACK_H_
#define MATH_KNAPSACK_H_

#include <vector>

namespace math {

// Solves knapsack problem.
// There are |N| items. i-th item's weight is |ws[i], and i-th item's
// value is |vs[i]|.
// Returns the max value.
int knapsack(int W, int N, const std::vector<int>& ws, const std::vector<int>& vs);

}

#endif // MATH_KNAPSACK_H_
