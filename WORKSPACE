git_repository(
    name = "gflags_repo",
    remote = "https://github.com/gflags/gflags.git",
    commit = "ac1a925c2bdec48e010020df93732badf75970e9",
)

bind(
    name = "gflags",
    actual = "@gflags_repo//:gflags",
)

new_git_repository(
    name = "gtest_repo",
    build_file = "third_party/gtest/gtest.BUILD",
    remote = "https://github.com/google/googletest.git",
    commit = "13206d6f53aaff844f2d3595a01ac83a29e383db",
)
