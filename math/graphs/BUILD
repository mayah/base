cc_library(
    name = "union_find",
    hdrs = [
        "union_find.h",
    ],
    srcs = [
        "union_find.cc",
    ],
    deps = [
        "//base/containers",
    ],
)

cc_test(
    name = "union_find_test",
    srcs = [
        "union_find_test.cc",
    ],
    deps = [
        ":union_find",
        "//third_party/glog",
        "//third_party/gtest",
    ],
)
