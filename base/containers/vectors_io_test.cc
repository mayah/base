#include "base/containers/vectors_io.h"

#include <gtest/gtest.h>

TEST(VectorsIOTest, print)
{
    std::stringstream ss;
    std::vector<int> vs { 1, 2, 3, 4, 5 };
    ss << vs;

    EXPECT_EQ("1 2 3 4 5", ss.str());
}
