#ifndef LEARNING_LINEAR_AROW_H_
#define LEARNING_LINEAR_AROW_H_

#include <cstddef>
#include <string>
#include <vector>

namespace learning {

// Arow is a linear classifier that uses ALOW algorithm.
class Arow {
public:
    explicit Arow(size_t size);

    size_t size() const { return size_; }

    // Returns +1 or -1.
    int predict(const std::vector<double>& features) const;

    // Calculates margin. If the |size| is not the same as |size_|,
    // the result is undefined.
    double margin(const double features[], size_t size) const;
    double margin(const std::vector<double>& features) const;
    double confidence(const std::vector<double>& features) const;

    int update(const std::vector<double>& features, int label, double learning_rate = 0.1);

    bool save(const std::string& filename) const;
    bool load(const std::string& filename);

private:
    const double size_; // feature size.

    // The size of |mean_| and |cov_| are |size_| + 1. It contanis bias term.
    std::vector<double> mean_;
    std::vector<double> cov_;
};

} // namespace learning

#endif // LEARNING_LINEAR_AROW_H_
