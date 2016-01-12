new_git_repository(
    name = "gtest_repo",
    build_file = "third_party/gtest.BUILD",
    remote = "https://github.com/google/googletest.git",
    commit = "13206d6f53aaff844f2d3595a01ac83a29e383db",
)

bind(
    name = "gtest",
    actual = "@gtest_repo//:gtest",
)
