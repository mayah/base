cc_library(
    name = "strings",
    srcs = [
        "ascii_ctype.cc",
        "replace_string.cc",
        "string_piece.cc",
        "strings.cc",
        "split.cc",
        "symbol.cc",
        "symbol_pool.cc",
        "utf8.cc",
    ],
    hdrs = [
        "ascii_ctype.h",
        "concat.h",
        "join.h",
        "replace_string.h",
        "string_piece.h",
        "strings.h",
        "split.h",
        "symbol.h",
        "symbol_pool.h",
        "utf8.h",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "ascii_ctype_test",
    srcs = [
        "ascii_ctype_test.cc",
    ],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ]
)

cc_test(
    name = "concat_test",
    srcs = [
        "concat_test.cc",
    ],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "join_test",
    srcs = [
        "join_test.cc",
    ],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "replace_string_test",
    srcs = [
        "replace_string_test.cc",
    ],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "strings_test",
    srcs = [
        "strings_test.cc",
    ],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "string_piece_test",
    srcs = [
        "string_piece_test.cc",
    ],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "split_test",
    srcs = [
        "split_test.cc",
    ],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "symbol_test",
    srcs = [
        "symbol_test.cc",
    ],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "utf8_test",
    srcs = [
        "utf8_test.cc"
    ],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ],
)
