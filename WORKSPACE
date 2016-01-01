new_git_repository(
    name = "gtest_repo",
    build_file = "third_party/gtest.BUILD",
    remote = "https://github.com/google/googletest.git",
    commit = "3aef7d7ddd3ac5d8257a484caffe6e80d29bca17"
)

bind(
    name = "gtest",
    actual = "@gtest_repo//:gtest",
)
