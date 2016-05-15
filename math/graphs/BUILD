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
        "//external:gtest",
        "//third_party/glog",
    ],
)
