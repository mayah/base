# ----------------------------------------------------------------------
# third-party libraries

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
    commit = "0a439623f75c029912728d80cb7f1b8b48739ca4",
)
