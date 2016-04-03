#include "learning/arow.h"

#include <gtest/gtest.h>
#include <random>

TEST(ArowTest, classify)
{
    // z = 2x + 4y + 1
    learning::Arow arow(2);

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (int i = 0; i < 1000; ++i) {
        double x = dist(mt);
        double y = dist(mt);
        double z = 2 * x + 4 * y + 1;
        arow.update(std::vector<double> { x, y }, z > 0 ? 1 : -1, 0.1);
    }

    const struct TestCase {
        TestCase(double x, double y) : x(x), y(y) {}

        double x;
        double y;
    } testcases[] = {
        TestCase(0, 0),
        TestCase(-1, -1),
        TestCase(-1, 1),
        TestCase(1, -1),
        TestCase(1, 1),
    };

    for (const auto& testcase : testcases) {
        double x = testcase.x;
        double y = testcase.y;
        double z = 2 * x + 4 * y + 1;

        int actual = arow.predict(std::vector<double> { x, y });
        int expected = z > 0 ? 1 : -1;

        EXPECT_EQ(expected, actual);
    }
}
