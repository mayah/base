#include "base/test/move_only.h"

#include <gtest/gtest.h>

TEST(MoveOnly, int)
{
    base::MoveOnlyInt x(3);
    base::MoveOnlyInt y = std::move(x);

    UNUSED_VARIABLE(y);

    // This doesn't compile.
    // base::MoveOnlyInt z(x);
}
