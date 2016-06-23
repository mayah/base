cc_library(
    name = "containers",
    srcs = [
        "byte_buffer.cc",
        "vectors.cc",
    ],
    hdrs = [
        "assoc_map.h",
        "blocking_queue.h",
        "byte_buffer.h",
        "flag_set.h",
        "flat_map.h",
        "flat_set.h",
        "linked_map.h",
        "matrix.h",
        "reverse_range.h",
        "ring_buffer.h",
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
    size = "small",
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
    size = "small",
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
    size = "small",
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
    size = "small",
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
    name = "flat_map_test",
    size = "small",
    srcs = [
        "flat_map_test.cc",
    ],
    deps = [
        ":containers",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "flat_set_test",
    size = "small",
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
    name = "linked_map_test",
    size = "small",
    srcs = [
        "linked_map_test.cc",
    ],
    deps = [
        ":containers",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "matrix_test",
    size = "small",
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
    size = "small",
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
    size = "small",
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
    size = "small",
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
    name = "ring_buffer_test",
    size = "small",
    srcs = [
        "ring_buffer_test.cc",
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
    size = "small",
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
    size = "small",
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
    size = "small",
    srcs = [
        "xrange_test.cc",
    ],
    deps = [
        ":containers",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)
