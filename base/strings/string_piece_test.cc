#include "base/strings/string_piece.h"

#include <string>

#include <gtest/gtest.h>

using namespace strings;

TEST(StringPieceTest, basic)
{
    StringPiece sp;

    EXPECT_TRUE(sp.empty());
    EXPECT_EQ(0UL, sp.size());
    EXPECT_EQ(nullptr, sp.data());
}

TEST(StringPieceTest, from_char_ptr)
{
    StringPiece sp("foo bar");

    EXPECT_FALSE(sp.empty());
    EXPECT_EQ(7UL, sp.size());
}

TEST(StringPieceTest, from_string)
{
    std::string s("foo bar");
    StringPiece sp(s);

    EXPECT_FALSE(sp.empty());
    EXPECT_EQ(7UL, sp.size());
}

TEST(StringPieceTest, with_nul)
{
    const char s[] = "abc\0def";
    StringPiece sp(s, 7);

    EXPECT_FALSE(sp.empty());
    EXPECT_EQ(7UL, sp.size());

    EXPECT_EQ('a', sp[0]);
    EXPECT_EQ('\0', sp[3]);

    EXPECT_EQ(7, sp.asString().size());
}

TEST(StringPieceTest, startsWith)
{
    StringPiece sp("foobar");

    EXPECT_TRUE(sp.startsWith(""));
    EXPECT_TRUE(sp.startsWith("f"));
    EXPECT_TRUE(sp.startsWith("foobar"));

    EXPECT_FALSE(sp.startsWith("oo"));
    EXPECT_FALSE(sp.startsWith("foobarbaz"));
}

TEST(StringPieceTest, endsWith)
{
    StringPiece sp("foobar");

    EXPECT_TRUE(sp.endsWith(""));
    EXPECT_TRUE(sp.endsWith("ar"));
    EXPECT_TRUE(sp.endsWith("foobar"));

    EXPECT_FALSE(sp.endsWith("oo"));
    EXPECT_FALSE(sp.endsWith("bazfoobar"));
}

TEST(StringPieceTest, compare)
{
    EXPECT_TRUE(StringPiece() == StringPiece());
    EXPECT_FALSE(StringPiece() != StringPiece());
    EXPECT_FALSE(StringPiece() < StringPiece());
    EXPECT_FALSE(StringPiece() > StringPiece());
    EXPECT_TRUE(StringPiece() <= StringPiece());
    EXPECT_TRUE(StringPiece() >= StringPiece());

    EXPECT_TRUE(StringPiece("a") == StringPiece("a"));
    EXPECT_FALSE(StringPiece("a") != StringPiece("a"));
    EXPECT_FALSE(StringPiece("a") < StringPiece("a"));
    EXPECT_FALSE(StringPiece("a") > StringPiece("a"));
    EXPECT_TRUE(StringPiece("a") <= StringPiece("a"));
    EXPECT_TRUE(StringPiece("a") >= StringPiece("a"));

    EXPECT_FALSE(StringPiece("a") == StringPiece("ab"));
    EXPECT_TRUE(StringPiece("a") != StringPiece("ab"));
    EXPECT_TRUE(StringPiece("a") < StringPiece("ab"));
    EXPECT_FALSE(StringPiece("a") > StringPiece("ab"));
    EXPECT_TRUE(StringPiece("a") <= StringPiece("ab"));
    EXPECT_FALSE(StringPiece("a") >= StringPiece("ab"));

    EXPECT_FALSE(StringPiece("ab") == StringPiece("a"));
    EXPECT_TRUE(StringPiece("ab") != StringPiece("a"));
    EXPECT_FALSE(StringPiece("ab") < StringPiece("a"));
    EXPECT_TRUE(StringPiece("ab") > StringPiece("a"));
    EXPECT_FALSE(StringPiece("ab") <= StringPiece("a"));
    EXPECT_TRUE(StringPiece("ab") >= StringPiece("a"));

    EXPECT_FALSE(StringPiece("aa") == StringPiece("ab"));
    EXPECT_TRUE(StringPiece("aa") != StringPiece("ab"));
    EXPECT_TRUE(StringPiece("aa") < StringPiece("ab"));
    EXPECT_FALSE(StringPiece("aa") > StringPiece("ab"));
    EXPECT_TRUE(StringPiece("aa") <= StringPiece("ab"));
    EXPECT_FALSE(StringPiece("aa") >= StringPiece("ab"));
}

TEST(StringPieceTest, find)
{
    StringPiece sp("abcdefg");

    EXPECT_EQ(0UL, sp.find(""));
    EXPECT_EQ(2UL, sp.find("", 2));

    EXPECT_EQ(0UL, sp.find("abc"));
    EXPECT_EQ(1UL, sp.find("bc"));
    EXPECT_EQ(2UL, sp.find("c"));

    EXPECT_EQ(StringPiece::npos, sp.find("bca"));

    StringPiece sp2("ababab");
    EXPECT_EQ(0UL, sp2.find("ab"));
    EXPECT_EQ(2UL, sp2.find("ab", 1));
    EXPECT_EQ(2UL, sp2.find("ab", 2));
    EXPECT_EQ(4UL, sp2.find("ab", 3));
    EXPECT_EQ(4UL, sp2.find("ab", 4));
    EXPECT_EQ(StringPiece::npos, sp2.find("ab", 5));
    EXPECT_EQ(StringPiece::npos, sp2.find("ab", 6));
    EXPECT_EQ(StringPiece::npos, sp2.find("ab", 7));
}

TEST(StringPieceTest, rfind)
{
    std::string s("abcdefg");
    StringPiece sp(s);

    EXPECT_EQ(7UL, sp.rfind(""));

    EXPECT_EQ(0UL, sp.rfind("a"));
    EXPECT_EQ(1UL, sp.rfind("b"));
    EXPECT_EQ(2UL, sp.rfind("c"));
    EXPECT_EQ(3UL, sp.rfind("d"));
    EXPECT_EQ(4UL, sp.rfind("e"));
    EXPECT_EQ(5UL, sp.rfind("f"));
    EXPECT_EQ(6UL, sp.rfind("g"));
    EXPECT_EQ(StringPiece::npos, sp.rfind("h"));

    EXPECT_EQ(0UL, sp.rfind("ab"));
    EXPECT_EQ(0UL, sp.rfind("abc"));

    EXPECT_EQ(1UL, sp.rfind("bcdefg"));
    EXPECT_EQ(1UL, sp.rfind("bcdef"));
    EXPECT_EQ(1UL, sp.rfind("bcde"));

    EXPECT_EQ(StringPiece::npos, sp.rfind("bcdefgh"));

    EXPECT_EQ(0UL, sp.rfind("a", 2));
    EXPECT_EQ(1UL, sp.rfind("b", 2));
    EXPECT_EQ(2UL, sp.rfind("c", 2));
    EXPECT_EQ(StringPiece::npos, sp.rfind("d", 2));

    EXPECT_EQ(0UL, sp.rfind("ab", 2));
    EXPECT_EQ(1UL, sp.rfind("bc", 2));
    EXPECT_EQ(2UL, sp.rfind("cd", 2));
    EXPECT_EQ(StringPiece::npos, sp.rfind("de", 2));

    // Confirm std::string and StringPiece has the same behavior.
    EXPECT_EQ(2UL, s.rfind("c", 2));
    EXPECT_EQ(std::string::npos, s.rfind("d", 2));
    EXPECT_EQ(2UL, s.rfind("cd", 2));
    EXPECT_EQ(std::string::npos, s.rfind("de", 2));
}

TEST(StringPieceTest, substr)
{
    StringPiece sp("abc");

    EXPECT_EQ("abc", sp.substr(0));
    EXPECT_EQ("bc", sp.substr(1));
    EXPECT_EQ("c", sp.substr(2));
    EXPECT_EQ("", sp.substr(3));
    EXPECT_EQ("", sp.substr(4));

    EXPECT_EQ("", sp.substr(1, 0));
    EXPECT_EQ("b", sp.substr(1, 1));
    EXPECT_EQ("bc", sp.substr(1, 2));
    EXPECT_EQ("bc", sp.substr(1, 3));
}
