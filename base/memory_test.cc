#include "base/memory.h"

#include <gtest/gtest.h>

TEST(UniqueFree, basic)
{
    base::unique_ptr_malloc<char> x(static_cast<char*>(malloc(100)));
}
