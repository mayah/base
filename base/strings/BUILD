cc_library(
    name = "strings",
    srcs = [
        "string_piece.cc",
        "strings.cc",
    ],
    hdrs = [
        "string_piece.h",
        "strings.h",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "strings_test",
    srcs = [
        "strings_test.cc",
    ],
    copts = [],
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
    copts = [],
    deps = [
        ":strings",
        "//external:gtest",
        "//third_party:glog",
    ],
)
