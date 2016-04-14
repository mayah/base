#include "base/strings/symbol.h"

#include <sstream>
#include <gtest/gtest.h>

#include "base/strings/symbol_pool.h"

TEST(SymbolTest, basic)
{
    strings::SymbolPool pool;

    strings::Symbol a1 = pool.intern("a");
    strings::Symbol b1 = pool.intern("b");

    strings::Symbol a2 = pool.intern(std::string("a"));
    strings::Symbol b2 = pool.intern(std::string("b"));

    EXPECT_EQ(a1, a2);
    EXPECT_EQ(a1.impl(), a2.impl());
    EXPECT_EQ(b1, b2);
    EXPECT_EQ(b1.impl(), b2.impl());

    EXPECT_NE(a1, b1);
    EXPECT_NE(a1, b2);
    EXPECT_NE(a2, b1);
    EXPECT_NE(a2, b2);
}

TEST(SymbolTest, ope)
{
    strings::SymbolPool pool;

    strings::Symbol a1 = pool.intern("a");

    std::stringstream ss;
    ss << a1.to_string();

    EXPECT_EQ("a", ss.str());
}
