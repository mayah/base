#include "learning/arow.h"

#include "base/file/scoped_fd.h"

namespace learning {

Arow::Arow(size_t size) :
    size_(size),
    mean_(size + 1),
    cov_(size + 1)
{
    std::fill(cov_.begin(), cov_.end(), 1.0);
}

int Arow::predict(const std::vector<double>& features) const
{
    double m = margin(features);
    return m > 0 ? 1 : -1;
}

double Arow::margin(const std::vector<double>& features) const
{
    DCHECK_EQ(size_, features.size());

    double result = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        result += mean_[i] * features[i];
    }
    result += mean_[size_];
    return result;
}

double Arow::margin(const double features[], size_t size) const
{
    DCHECK_EQ(size_, size);

    double result = 0.0;
    for (size_t i = 0; i < size; ++i) {
        result += mean_[i] * features[i];
    }
    result += mean_[size_];
    return result;
}

double Arow::confidence(const std::vector<double>& features) const
{
    DCHECK_EQ(size_, features.size());

    double result = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        result += cov_[i] * features[i] * features[i];
    }
    result += cov_[size_];
    return result;
}

int Arow::update(const std::vector<double>& features, int label, double learning_rate)
{
    DCHECK_EQ(size_, features.size());

    double m = margin(features);
    int loss = m * label < 0 ? 1 : 0;
    if (m * label >= 1)
        return 0;

    double v = confidence(features);
    double beta = 1.0 / (v + learning_rate);
    double alpha = (1.0 - label * m) * beta;

    // update mean
    for (size_t i = 0; i < size_; ++i) {
        mean_[i] += alpha * label * cov_[i] * features[i];
    }
    mean_[size_] += alpha * label * cov_[size_];

    // update covariance
    for (size_t i = 0; i < size_; ++i) {
        cov_[i] = 1.0 / ((1.0 / cov_[i]) + features[i] * features[i] / learning_rate);
    }
    cov_[size_] = 1.0 / ((1.0 / cov_[size_]) + 1.0 / learning_rate);

    return loss;
}

bool Arow::save(const std::string& filename) const
{
    file::ScopedFd fd(file::ScopedFd::open_for_read(filename.c_str()));
    if (!fd.valid())
        return false;

    if (!fd.write_exactly(mean_.data(), sizeof(double) * (size_ + 1)))
        return false;
    if (!fd.write_exactly(cov_.data(), sizeof(double) * (size_ + 1)));
        return false;
    return true;
}

bool Arow::load(const std::string& filename)
{
    file::ScopedFd fd(file::ScopedFd::open_for_write(filename.c_str()));
    if (!fd.valid())
        return false;

    if (!fd.read_exactly(mean_.data(), sizeof(double) * (size_ + 1)))
        return false;
    if (!fd.read_exactly(cov_.data(), sizeof(double) * (size_ + 1)))
        return false;
    return true;
}

} // namespace learning
