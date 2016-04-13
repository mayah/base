cc_library(
    name = "math",
    hdrs = [
        "gauss.h",
        "knapsack.h",
        "math.h",
        "sigmoid.h",
    ],
    srcs = [
        "gauss.cc",
        "knapsack.cc",
        "math.cc",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "gauss_test",
    srcs = [
        "gauss_test.cc",
    ],
    deps = [
        ":math",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "math_test",
    srcs = [
        "math_test.cc",
    ],
    deps = [
        ":math",
        "//external:gtest",
        "//third_party:glog",
    ],
)
