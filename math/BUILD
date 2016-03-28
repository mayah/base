cc_library(
    name = "math",
    hdrs = [
        "gauss.h",
        "sigmoid.h",
        "math.h",
    ],
    srcs = [
        "gauss.cc",
        "math.cc",
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
