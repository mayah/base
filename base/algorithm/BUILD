cc_library(
    name = "algorithm",
    hdrs = [
        "fold.h",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "fold_test",
    size = "small",
    srcs = [
        "fold_test.cc",
    ],
    deps = [
        ":algorithm",
        "//third_party/glog",
        "//third_party/gtest",
    ],
)
