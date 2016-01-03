#include "base/file/path.h"

#include <gtest/gtest.h>

TEST(FilePathTest, isAbsolutePath)
{
  EXPECT_TRUE(file::isAbsolutePath("/"));
  EXPECT_TRUE(file::isAbsolutePath("/foo/bar"));
  EXPECT_TRUE(file::isAbsolutePath("//../foo/bar"));

  EXPECT_FALSE(file::isAbsolutePath(""));
  EXPECT_FALSE(file::isAbsolutePath("../"));
  EXPECT_FALSE(file::isAbsolutePath("foo/bar"));
}
