#include "base/time/time_stamp_counter.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>

using namespace std;

namespace base {

void TimeStampCounter::show_statistics() const
{
    int n = data_.size();
    if (n <= 1) {
        cout << "no enough data to show statistics" << endl;
        return;
    }

    double sum = 0.0;
    for (auto x : data_) {
        sum += x;
    }
    double average = sum / n;

    double diff_square_sum = 0.0;
    for (auto x : data_) {
        diff_square_sum += (x - average) * (x - average);
    }

    double deviation = pow(diff_square_sum / n, 0.5);

    cout << "        N = " << n << endl;
    cout << "      min = " << *min_element(data_.begin(), data_.end()) << endl;
    cout << "      max = " << *max_element(data_.begin(), data_.end()) << endl;
    cout << "  average = " << average << endl;
    cout << "deviation = " << deviation << endl;
}

} // namespace base
