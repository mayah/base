cc_library(
    name = "containers",
    srcs = [
        "vectors.cc",
    ],
    hdrs = [
        "reverse_range.h",
        "small_int_set.h",
        "slice.h",
        "vectors.h",
        "vectors_io.h",
        "xrange.h",
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
    name = "slice_test",
    srcs = [
        "slice_test.cc",
    ],
    deps = [
        ":containers",
        "//base",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "reverse_range_test",
    srcs = [
        "reverse_range_test.cc",
    ],
    deps = [
        ":containers",
        "//base",
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

cc_test(
    name = "xrange_test",
    srcs = [
        "xrange_test.cc"
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party:glog"
    ],
)
