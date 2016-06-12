#ifndef MATH_GEO_VECTOR_H_
#define MATH_GEO_VECTOR_H_

namespace geo {

class Vector2d {
public:
    Point(double x, double y) : x_(x), y_(y) {}

    double x() const { return x_; }
    double y() const { return y_; }

    void set_x(double x) { x_ = x; }
    void set_y(double y) { y_ = y; }

private:
    double x_;
    double y_;
};

} // namespace geo

#endif // MATH_GEO_VECTOR_H_
