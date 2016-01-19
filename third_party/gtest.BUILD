cc_library(
    name = "gtest",
    srcs = glob(
        ["googletest/src/*.cc"],
        exclude = ["googletest/src/gtest-all.cc"]
    ),
    hdrs = glob(
        ["googletest/**/*.h"],
    ),
    includes = [
        "googletest/include",
    ],
    copts = [
        "-Iexternal/gtest_repo/googletest",
        "-Iexternal/gtest_repo/googletest/include",
    ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "gtest_prod",
    srcs = [],
    hdrs = ["googletest/include/gtest/gtest_prod.h"],
    includes = [
        "googletest/include",
    ],
    visibility = ["//visibility:public"],
)
