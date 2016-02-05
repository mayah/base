#include "base/file/path.h"

#include <gtest/gtest.h>

using namespace file;

TEST(FilePathTest, is_absolute_path)
{
    EXPECT_TRUE(is_absolute_path("/"));
    EXPECT_TRUE(is_absolute_path("/foo/bar"));
    EXPECT_TRUE(is_absolute_path("//../foo/bar"));

    EXPECT_FALSE(is_absolute_path(""));
    EXPECT_FALSE(is_absolute_path("../"));
    EXPECT_FALSE(is_absolute_path("foo/bar"));
}

TEST(FilePathTest, join_path)
{
    EXPECT_EQ("/foo/bar", join_path("/foo", "bar"));
    EXPECT_EQ("/foo/bar", join_path("/foo", "/bar"));
    EXPECT_EQ("foo/bar", join_path("foo", "bar"));
    EXPECT_EQ("foo/bar", join_path("foo", "/bar"));

    EXPECT_EQ("foo", join_path("foo", ""));
    EXPECT_EQ("/foo", join_path("/foo", ""));

    EXPECT_EQ("foo", join_path("", "foo"));
    EXPECT_EQ("/foo", join_path("", "/foo"));

    EXPECT_EQ("/foo/bar/baz", join_path("/foo", "bar/baz"));
    EXPECT_EQ("/foo/bar/baz", join_path("/foo/bar", "/baz"));
}

TEST(FilePathTest, join_path_respect_absolute)
{
    EXPECT_EQ("/foo/bar", join_path_respect_absolute("/foo", "bar"));
    EXPECT_EQ("/bar", join_path_respect_absolute("/foo", "/bar"));
    EXPECT_EQ("foo/bar", join_path_respect_absolute("foo", "bar"));
    EXPECT_EQ("/bar", join_path_respect_absolute("foo", "/bar"));

    EXPECT_EQ("foo", join_path_respect_absolute("foo", ""));
    EXPECT_EQ("/foo", join_path_respect_absolute("/foo", ""));

    EXPECT_EQ("foo", join_path_respect_absolute("", "foo"));
    EXPECT_EQ("/foo", join_path_respect_absolute("", "/foo"));

    EXPECT_EQ("/foo/bar/baz", join_path_respect_absolute("/foo", "bar/baz"));
    EXPECT_EQ("/baz", join_path_respect_absolute("/foo/bar", "/baz"));
}

TEST(FilePathTest, basename)
{
    EXPECT_EQ("", file::basename(""));

    EXPECT_EQ("lib", file::basename("/usr/lib"));
    EXPECT_EQ("usr", file::basename("/usr/"));
    EXPECT_EQ("usr", file::basename("usr"));
    EXPECT_EQ("", file::basename("/"));
    EXPECT_EQ(".", file::basename("."));
    EXPECT_EQ("..", file::basename(".."));
}

TEST(FilePathTest, dirname)
{
    EXPECT_EQ("", file::dirname(""));

    EXPECT_EQ("/usr", file::dirname("/usr/lib"));
    EXPECT_EQ("/", file::dirname("/usr/"));
    EXPECT_EQ("", file::dirname("usr"));
    EXPECT_EQ("/", file::dirname("/"));
    EXPECT_EQ("", file::dirname("."));
    EXPECT_EQ("", file::dirname(".."));
}

TEST(FilePathTest, stem)
{
    EXPECT_EQ("", file::stem(""));
    EXPECT_EQ("", file::stem("."));
    EXPECT_EQ(".", file::stem(".."));

    EXPECT_EQ("foo", file::stem("foo"));
    EXPECT_EQ("foo", file::stem("foo.txt"));
    EXPECT_EQ("foo", file::stem("/usr/local/bin/foo"));
    EXPECT_EQ("foo", file::stem("/usr/local/bin/foo.txt"));
    EXPECT_EQ("bin", file::stem("/usr/local/bin/"));
    EXPECT_EQ("bin", file::stem("/usr/local/bin.dir/"));
    EXPECT_EQ("", file::stem("/tmp/.foo"));
}

TEST(FilePathTest, extension)
{
    EXPECT_EQ("", file::extension(""));
    EXPECT_EQ(".", file::extension("."));
    EXPECT_EQ(".", file::extension(".."));

    EXPECT_EQ("", file::extension("foo"));
    EXPECT_EQ(".txt", file::extension("foo.txt"));
    EXPECT_EQ("", file::extension("/usr/local/bin/foo"));
    EXPECT_EQ(".txt", file::extension("/usr/local/bin/foo.txt"));
    EXPECT_EQ("", file::extension("/usr/local/bin/"));
    EXPECT_EQ(".dir", file::extension("/usr/local/bin.dir/"));
    EXPECT_EQ(".foo", file::extension("/tmp/.foo"));
}
