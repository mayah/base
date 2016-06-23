cc_library(
    name = "strings",
    srcs = [
        "ascii_ctype.cc",
        "replace_string.cc",
        "split.cc",
        "string_piece.cc",
        "strings.cc",
        "symbol.cc",
        "symbol_pool.cc",
        "utf8.cc",
    ],
    hdrs = [
        "ascii_ctype.h",
        "concat.h",
        "join.h",
        "replace_string.h",
        "split.h",
        "string_piece.h",
        "strings.h",
        "symbol.h",
        "symbol_pool.h",
        "utf8.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//third_party/glog",
    ],
)

cc_test(
    name = "ascii_ctype_test",
    size = "small",
    srcs = [
        "ascii_ctype_test.cc",
    ],
    deps = [
        ":strings",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "concat_test",
    size = "small",
    srcs = [
        "concat_test.cc",
    ],
    deps = [
        ":strings",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "join_test",
    size = "small",
    srcs = [
        "join_test.cc",
    ],
    deps = [
        ":strings",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "replace_string_test",
    size = "small",
    srcs = [
        "replace_string_test.cc",
    ],
    deps = [
        ":strings",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "strings_test",
    size = "small",
    srcs = [
        "strings_test.cc",
    ],
    deps = [
        ":strings",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "string_piece_test",
    size = "small",
    srcs = [
        "string_piece_test.cc",
    ],
    deps = [
        ":strings",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "split_test",
    size = "small",
    srcs = [
        "split_test.cc",
    ],
    deps = [
        ":strings",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "symbol_test",
    size = "small",
    srcs = [
        "symbol_test.cc",
    ],
    deps = [
        ":strings",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "utf8_test",
    size = "small",
    srcs = [
        "utf8_test.cc",
    ],
    deps = [
        ":strings",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)
