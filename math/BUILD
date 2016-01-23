cc_library(
    name = "math",
    hdrs = [
        "math.h",
    ],
    srcs = [
        "math.cc",
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
