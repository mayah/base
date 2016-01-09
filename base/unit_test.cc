#include "base/unit.h"

#include <gtest/gtest.h>

using namespace std;

TEST(UnitTest, ident)
{
    EXPECT_EQ(base::Unit(), base::Unit());
}
