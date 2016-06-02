cc_library(
    name = "containers",
    srcs = [
        "vectors.cc",
    ],
    hdrs = [
        "blocking_queue.h",
        "flag_set.h",
        "flat_set.h",
        "reverse_range.h",
        "slice.h",
        "static_vector.h",
        "vectors.h",
        "vectors_io.h",
        "xrange.h",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "blocking_queue_test",
    srcs = [
        "blocking_queue_test.cc",
    ],
    deps = [
        ":containers",
        "//base/concurrent",
        "//base/test:move_only",
        "//external:gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "flag_set_test",
    srcs = [
        "flag_set_test.cc",
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "flat_set_test",
    srcs = [
        "flat_set_test.cc",
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "static_vector_test",
    srcs = [
        "static_vector_test.cc",
    ],
    deps = [
        ":containers",
        "//base",
        "//external:gtest",
        "//third_party/glog",
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
        "//third_party/glog",
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
        "//third_party/glog",
    ],
)

cc_test(
    name = "vectors_test",
    srcs = [
        "vectors_test.cc",
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "vectors_io_test",
    srcs = [
        "vectors_io_test.cc",
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "xrange_test",
    srcs = [
        "xrange_test.cc",
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party/glog",
    ],
)
