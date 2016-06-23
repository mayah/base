cc_library(
    name = "math",
    hdrs = [
        "gauss.h",
        "knapsack.h",
        "math.h",
        "prime.h",
        "sigmoid.h",
    ],
    srcs = [
        "gauss.cc",
        "knapsack.cc",
        "prime.cc",
        "math.cc",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "gauss_test",
    size = "small",
    srcs = [
        "gauss_test.cc",
    ],
    deps = [
        ":math",
        "//third_party/glog",
        "//third_party/gtest",
    ],
)

cc_test(
    name = "math_test",
    size = "small",
    srcs = [
        "math_test.cc",
    ],
    deps = [
        ":math",
        "//third_party/glog",
        "//third_party/gtest",
    ],
)

cc_test(
    name = "prime_test",
    size = "small",
    srcs = [
        "prime_test.cc",
    ],
    deps = [
        ":math",
        "//third_party/glog",
        "//third_party/gtest",
    ],
)
