git_repository(
    name = "gflags_repo",
    remote = "https://github.com/gflags/gflags.git",
    commit = "d701ceac73be2c43b6e7b97474184e626fded88b",
)

bind(
    name = "gflags",
    actual = "@gflags_repo//:gflags",
)

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

bind(
    name = "gtest_prod",
    actual = "@gtest_repo//:gtest_prod",
)
