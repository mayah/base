cc_library(
    name = "containers",
    srcs = [
        "byte_buffer.cc",
        "vectors.cc",
    ],
    hdrs = [
        "assoc_map.h",
        "byte_buffer.h",
        "blocking_queue.h",
        "flag_set.h",
        "flat_set.h",
        "matrix.h",
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
    name = "assoc_map_test",
    srcs = [
        "assoc_map_test.cc",
    ],
    deps = [
        ":containers",
        "//third_party/gtest",
        "//third_party/glog",
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
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "byte_buffer_test",
    srcs = [
        "byte_buffer_test.cc",
    ],
    deps = [
        ":containers",
        "//third_party/gtest",
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
        "//third_party/gtest",
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
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "matrix_test",
    srcs = [
        "matrix_test.cc",
    ],
    deps = [
        ":containers",
        "//third_party/gtest",
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
        "//third_party/gtest",
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
        "//third_party/gtest",
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
        "//third_party/gtest",
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
        "//third_party/gtest",
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
        "//third_party/gtest",
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
        "//third_party/gtest",
        "//third_party/glog",
    ],
)
