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
