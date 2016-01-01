#include "base/unit.h"

#include <gtest/gtest.h>

using namespace std;

TEST(unit_test, ident)
{
    EXPECT_EQ(base::Unit(), base::Unit());
}
