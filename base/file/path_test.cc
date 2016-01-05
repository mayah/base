#include "base/file/path.h"

#include <gtest/gtest.h>

using namespace file;

TEST(FilePathTest, isAbsolutePath)
{
    EXPECT_TRUE(isAbsolutePath("/"));
    EXPECT_TRUE(isAbsolutePath("/foo/bar"));
    EXPECT_TRUE(isAbsolutePath("//../foo/bar"));

    EXPECT_FALSE(isAbsolutePath(""));
    EXPECT_FALSE(isAbsolutePath("../"));
    EXPECT_FALSE(isAbsolutePath("foo/bar"));
}

TEST(FilePathTest, joinPath)
{
    EXPECT_EQ("/foo/bar", joinPath("/foo", "bar"));
    EXPECT_EQ("/foo/bar", joinPath("/foo", "/bar"));
    EXPECT_EQ("foo/bar", joinPath("foo", "bar"));
    EXPECT_EQ("foo/bar", joinPath("foo", "/bar"));

    EXPECT_EQ("foo", joinPath("foo", ""));
    EXPECT_EQ("/foo", joinPath("/foo", ""));

    EXPECT_EQ("foo", joinPath("", "foo"));
    EXPECT_EQ("/foo", joinPath("", "/foo"));

    EXPECT_EQ("/foo/bar/baz", joinPath("/foo", "bar/baz"));
    EXPECT_EQ("/foo/bar/baz", joinPath("/foo/bar", "/baz"));
}

TEST(FilePathTest, joinPathRespectAbsolute)
{
    EXPECT_EQ("/foo/bar", joinPathRespectAbsolute("/foo", "bar"));
    EXPECT_EQ("/bar", joinPathRespectAbsolute("/foo", "/bar"));
    EXPECT_EQ("foo/bar", joinPathRespectAbsolute("foo", "bar"));
    EXPECT_EQ("/bar", joinPathRespectAbsolute("foo", "/bar"));

    EXPECT_EQ("foo", joinPathRespectAbsolute("foo", ""));
    EXPECT_EQ("/foo", joinPathRespectAbsolute("/foo", ""));

    EXPECT_EQ("foo", joinPathRespectAbsolute("", "foo"));
    EXPECT_EQ("/foo", joinPathRespectAbsolute("", "/foo"));

    EXPECT_EQ("/foo/bar/baz", joinPathRespectAbsolute("/foo", "bar/baz"));
    EXPECT_EQ("/baz", joinPathRespectAbsolute("/foo/bar", "/baz"));
}
