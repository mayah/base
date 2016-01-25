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

    EXPECT_EQ(7, sp.as_string().size());
}

TEST(StringPieceTest, starts_with)
{
    StringPiece sp("foobar");

    EXPECT_TRUE(sp.starts_with(""));
    EXPECT_TRUE(sp.starts_with("f"));
    EXPECT_TRUE(sp.starts_with("foobar"));

    EXPECT_FALSE(sp.starts_with("oo"));
    EXPECT_FALSE(sp.starts_with("foobarbaz"));
}

TEST(StringPieceTest, ends_with)
{
    StringPiece sp("foobar");

    EXPECT_TRUE(sp.ends_with(""));
    EXPECT_TRUE(sp.ends_with("ar"));
    EXPECT_TRUE(sp.ends_with("foobar"));

    EXPECT_FALSE(sp.ends_with("oo"));
    EXPECT_FALSE(sp.ends_with("bazfoobar"));
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

TEST(StringPieceTest, find_char)
{
    StringPiece sp("abcdefg");

    EXPECT_EQ(0UL, sp.find('a'));
    EXPECT_EQ(StringPiece::npos, sp.find('a', 1));
    EXPECT_EQ(1UL, sp.find('b'));
    EXPECT_EQ(1UL, sp.find('b', 1));
    EXPECT_EQ(StringPiece::npos, sp.find('b', 2));
    EXPECT_EQ(2UL, sp.find('c'));
    EXPECT_EQ(2UL, sp.find('c', 1));
    EXPECT_EQ(StringPiece::npos, sp.find('c', 3));
}

TEST(StringPieceTest, rfind)
{
    StringPiece s("abcdefg");
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
    EXPECT_EQ(s.rfind("c", 2), sp.rfind("c", 2));
    EXPECT_EQ(s.rfind("d", 2), sp.rfind("d", 2));
    EXPECT_EQ(s.rfind("cd", 2), sp.rfind("cd", 2));
    EXPECT_EQ(s.rfind("de", 2), sp.rfind("de", 2));
}

TEST(StringPieceTest, rfind_char)
{
    StringPiece s("abcabc");
    StringPiece sp(s);

    EXPECT_EQ(StringPiece::npos, sp.rfind('d'));

    EXPECT_EQ(3UL, sp.rfind('a'));
    EXPECT_EQ(3UL, sp.rfind('a', 3));
    EXPECT_EQ(0UL, sp.rfind('a', 1));
    EXPECT_EQ(0UL, sp.rfind('a', 0));

    // Confirm std::string and StringPiece has the same behavior.
    EXPECT_EQ(s.rfind('a'), sp.rfind('a'));
    EXPECT_EQ(s.rfind('a', 3), sp.rfind('a', 3));
    EXPECT_EQ(s.rfind('a', 1), sp.rfind('a', 1));
    EXPECT_EQ(s.rfind('a', 0), sp.rfind('a', 0));
}

TEST(StringPieceTest, find_first_of)
{
    std::string s("abcabc");
    StringPiece sp(s);

    EXPECT_EQ(StringPiece::npos, sp.find_first_of(""));

    EXPECT_EQ(0, sp.find_first_of('a'));
    EXPECT_EQ(3, sp.find_first_of('a', 1));
    EXPECT_EQ(StringPiece::npos, sp.find_first_of('a', 4));

    EXPECT_EQ(1, sp.find_first_of('b'));
    EXPECT_EQ(1, sp.find_first_of('b', 1));
    EXPECT_EQ(4, sp.find_first_of('b', 2));
    EXPECT_EQ(StringPiece::npos, sp.find_first_of('b', 5));

    EXPECT_EQ(StringPiece::npos, sp.find_first_of('d'));

    EXPECT_EQ(0, sp.find_first_of("ab"));
    EXPECT_EQ(1, sp.find_first_of("ab", 1));
    EXPECT_EQ(3, sp.find_first_of("ab", 2));
    EXPECT_EQ(2, sp.find_first_of("ac", 2));
    EXPECT_EQ(2, sp.find_first_of("cd", 2));
    EXPECT_EQ(5, sp.find_first_of("cd", 3));
    EXPECT_EQ(StringPiece::npos, sp.find_first_of("de", 2));

    // Confirm std::string and StringPiece has the same behavior.
    EXPECT_EQ(s.find_first_of(""), sp.find_first_of(""));
    EXPECT_EQ(s.find_first_of("a"), sp.find_first_of("a"));
    EXPECT_EQ(s.find_first_of("a", 1), sp.find_first_of("a", 1));
    EXPECT_EQ(s.find_first_of("a", 2), sp.find_first_of("a", 2));
    EXPECT_EQ(s.find_first_of("ab"), sp.find_first_of("ab"));
    EXPECT_EQ(s.find_first_of("bc"), sp.find_first_of("bc"));
    EXPECT_EQ(s.find_first_of("ac", 1), sp.find_first_of("ac", 1));
    EXPECT_EQ(s.find_first_of("ac", 3), sp.find_first_of("ac", 3));
}

TEST(StringPieceTest, find_first_not_of)
{
    std::string s("abcabc");
    StringPiece sp(s);

    EXPECT_EQ(0, sp.find_first_not_of(""));

    EXPECT_EQ(1, sp.find_first_not_of('a'));
    EXPECT_EQ(1, sp.find_first_not_of('a', 1));

    EXPECT_EQ(0, sp.find_first_not_of('b'));
    EXPECT_EQ(2, sp.find_first_not_of('b', 1));
    EXPECT_EQ(2, sp.find_first_not_of('b', 2));
    EXPECT_EQ(3, sp.find_first_not_of('c', 2));

    EXPECT_EQ(0, sp.find_first_not_of('d'));

    EXPECT_EQ(2, sp.find_first_not_of("ab"));
    EXPECT_EQ(2, sp.find_first_not_of("ab", 1));
    EXPECT_EQ(2, sp.find_first_not_of("ab", 2));
    EXPECT_EQ(StringPiece::npos, sp.find_first_not_of("abc", 2));
    EXPECT_EQ(4, sp.find_first_not_of("ac", 2));
    EXPECT_EQ(3, sp.find_first_not_of("cd", 2));
    EXPECT_EQ(2, sp.find_first_not_of("de", 2));

    // Confirm std::string and StringPiece has the same behavior.
    EXPECT_EQ(s.find_first_not_of(""), sp.find_first_not_of(""));
    EXPECT_EQ(s.find_first_not_of("a"), sp.find_first_not_of("a"));
    EXPECT_EQ(s.find_first_not_of("a", 1), sp.find_first_not_of("a", 1));
    EXPECT_EQ(s.find_first_not_of("a", 2), sp.find_first_not_of("a", 2));
    EXPECT_EQ(s.find_first_not_of("ab"), sp.find_first_not_of("ab"));
    EXPECT_EQ(s.find_first_not_of("bc"), sp.find_first_not_of("bc"));
    EXPECT_EQ(s.find_first_not_of("ac", 1), sp.find_first_not_of("ac", 1));
    EXPECT_EQ(s.find_first_not_of("ac", 3), sp.find_first_not_of("ac", 3));
    EXPECT_EQ(s.find_first_not_of("abc", 3), sp.find_first_not_of("abc"));
}

TEST(StringPieceTest, find_last_of)
{
    std::string s("abcabc");
    StringPiece sp(s);

    EXPECT_EQ(StringPiece::npos, sp.find_last_of(""));

    EXPECT_EQ(3, sp.find_last_of('a'));
    EXPECT_EQ(3, sp.find_last_of('a', 3));
    EXPECT_EQ(0, sp.find_last_of('a', 2));
    EXPECT_EQ(0, sp.find_last_of('a', 0));

    EXPECT_EQ(4, sp.find_last_of('b'));
    EXPECT_EQ(1, sp.find_last_of('b', 1));
    EXPECT_EQ(1, sp.find_last_of('b', 2));
    EXPECT_EQ(StringPiece::npos, sp.find_last_of('b', 0));

    EXPECT_EQ(StringPiece::npos, sp.find_last_of('d'));

    EXPECT_EQ(4, sp.find_last_of("ab"));
    EXPECT_EQ(1, sp.find_last_of("ab", 1));
    EXPECT_EQ(1, sp.find_last_of("ab", 2));
    EXPECT_EQ(2, sp.find_last_of("ac", 2));
    EXPECT_EQ(2, sp.find_last_of("cd", 2));
    EXPECT_EQ(StringPiece::npos, sp.find_last_of("cd", 1));
    EXPECT_EQ(2, sp.find_last_of("cd", 3));
    EXPECT_EQ(StringPiece::npos, sp.find_last_of("de", 2));

    // Confirm std::string and StringPiece has the same behavior.
    EXPECT_EQ(s.find_last_of(""), sp.find_last_of(""));
    EXPECT_EQ(s.find_last_of("a"), sp.find_last_of("a"));
    EXPECT_EQ(s.find_last_of("a", 1), sp.find_last_of("a", 1));
    EXPECT_EQ(s.find_last_of("a", 2), sp.find_last_of("a", 2));
    EXPECT_EQ(s.find_last_of("a", 3), sp.find_last_of("a", 3));
    EXPECT_EQ(s.find_last_of("a", 4), sp.find_last_of("a", 4));
    EXPECT_EQ(s.find_last_of("b"), sp.find_last_of("b"));
    EXPECT_EQ(s.find_last_of("b", 0), sp.find_last_of("b", 0));
    EXPECT_EQ(s.find_last_of("ab"), sp.find_last_of("ab"));
    EXPECT_EQ(s.find_last_of("bc"), sp.find_last_of("bc"));
    EXPECT_EQ(s.find_last_of("ac", 1), sp.find_last_of("ac", 1));
    EXPECT_EQ(s.find_last_of("ac", 3), sp.find_last_of("ac", 3));
}

TEST(StringPieceTest, find_last_not_of)
{
    std::string s("abcabc");
    StringPiece sp(s);

    EXPECT_EQ(5, sp.find_last_not_of(""));

    EXPECT_EQ(5, sp.find_last_not_of('a'));
    EXPECT_EQ(1, sp.find_last_not_of('a', 1));
    EXPECT_EQ(StringPiece::npos, sp.find_last_not_of('a', 0));

    EXPECT_EQ(5, sp.find_last_not_of('b'));
    EXPECT_EQ(3, sp.find_last_not_of('b', 4));
    EXPECT_EQ(2, sp.find_last_not_of('b', 2));
    EXPECT_EQ(0, sp.find_last_not_of('b', 1));
    EXPECT_EQ(1, sp.find_last_not_of('c', 2));

    EXPECT_EQ(5, sp.find_last_not_of('d'));

    EXPECT_EQ(5, sp.find_last_not_of("ab"));
    EXPECT_EQ(StringPiece::npos, sp.find_last_not_of("ab", 1));
    EXPECT_EQ(2, sp.find_last_not_of("ab", 2));
    EXPECT_EQ(StringPiece::npos, sp.find_last_not_of("abc", 2));
    EXPECT_EQ(1, sp.find_last_not_of("ac", 3));
    EXPECT_EQ(1, sp.find_last_not_of("cd", 2));
    EXPECT_EQ(2, sp.find_last_not_of("de", 2));

    // Confirm std::string and StringPiece has the same behavior.
    EXPECT_EQ(s.find_last_not_of(""), sp.find_last_not_of(""));
    EXPECT_EQ(s.find_last_not_of("a"), sp.find_last_not_of("a"));
    EXPECT_EQ(s.find_last_not_of("a", 0), sp.find_last_not_of("a", 0));
    EXPECT_EQ(s.find_last_not_of("a", 1), sp.find_last_not_of("a", 1));
    EXPECT_EQ(s.find_last_not_of("a", 2), sp.find_last_not_of("a", 2));
    EXPECT_EQ(s.find_last_not_of("ab"), sp.find_last_not_of("ab"));
    EXPECT_EQ(s.find_last_not_of("bc"), sp.find_last_not_of("bc"));
    EXPECT_EQ(s.find_last_not_of("ac", 1), sp.find_last_not_of("ac", 1));
    EXPECT_EQ(s.find_last_not_of("ac", 3), sp.find_last_not_of("ac", 3));
    EXPECT_EQ(s.find_last_not_of("abc", 3), sp.find_last_not_of("abc", 3));
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

TEST(StringPiece, chomp)
{
    EXPECT_EQ("", StringPiece("").chomp());
    EXPECT_EQ("a", StringPiece("a").chomp());
    EXPECT_EQ("a", StringPiece("a\r").chomp());
    EXPECT_EQ("a", StringPiece("a\r\n").chomp());
    EXPECT_EQ("a", StringPiece("a\n").chomp());
    EXPECT_EQ("a\n", StringPiece("a\n\n").chomp());
    EXPECT_EQ("a\n", StringPiece("a\n\r").chomp());
    EXPECT_EQ("a\r\n", StringPiece("a\r\n\n").chomp());
}
