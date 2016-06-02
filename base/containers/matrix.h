#ifndef BASE_CONTAINERS_MATRIX_H_
#define BASE_CONTAINERS_MATRIX_H_

// Matrix<T> is 2-dimensional array.

#include <cstddef>
#include <vector>

namespace base {

template<typename T>
class Matrix {
public:
    Matrix(std::size_t height, std::size_t width) :
        height_(height),
        width_(width),
        data_(height, std::vector<T>(width)) {}

    std::size_t height() const { return height_; }
    std::size_t width() const { return width_; }

    T& operator()(size_t y, size_t x) { return data_[y][x]; }
    const T& operator()(size_t y, size_t x) const { return data_[y][x]; }

private:
    const std::size_t height_;
    const std::size_t width_;
    std::vector<std::vector<T>> data_;
};

} // namespace base

#endif // BASE_CONTAINERS_MATRIX_H_
