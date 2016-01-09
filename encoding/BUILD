cc_library(
    name = "hex",
    srcs = [
        "hex.cc",
    ],
    hdrs = [
        "hex.h",
    ],
    deps = [
        "//base/strings",
    ],
    visibility = [
        "//visibility:public",
    ]
)

cc_test(
    name = "hex_test",
    srcs = [
        "hex_test.cc",
    ],
    deps = [
        ":hex",
        "//base",
        "//external:gtest",
        "//third_party:glog",
    ],
)