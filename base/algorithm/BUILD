cc_library(
    name = "algorithm",
    hdrs = [
        "fold.h",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "fold_test",
    srcs = [
        "fold_test.cc",
    ],
    deps = [
        ":algorithm",
        "//external:gtest",
        "//third_party/glog",
    ],
)
