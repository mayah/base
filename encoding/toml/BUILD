cc_library(
    name = "toml",
    srcs = [
        "toml.cc",
    ],
    hdrs = [
        "toml.h",
    ],
    visibility = [
        "//visibility:public",
    ]
)

cc_test(
    name = "toml_value_test",
    srcs = [
        "toml_value_test.cc",
    ],
    deps = [
        ":toml",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "toml_lexer_test",
    srcs = [
        "toml_lexer_test.cc",
    ],
    deps = [
        ":toml",
        "//external:gtest",
        "//third_party:glog",
    ],
)

cc_test(
    name = "toml_parser_test",
    srcs = [
        "toml_parser_test.cc",
    ],
    deps = [
        ":toml",
        "//external:gtest",
        "//third_party:glog",
    ],
)
