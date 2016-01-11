cc_library(
    name = "containers",
    srcs = [
    ],
    hdrs = [
        "small_int_set.h",
        "vectors.h",
        "vectors_io.h"
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "containers_test",
    srcs = [
        "small_int_set_test.cc",
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "vectors_test",
    srcs = [
        "vectors_test.cc"
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party:glog"
    ],
)

cc_test(
    name = "vectors_io_test",
    srcs = [
        "vectors_io_test.cc"
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party:glog"
    ],
)
