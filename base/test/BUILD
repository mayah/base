cc_library(
    name = "move_only",
    hdrs = [
        "move_only.h",
    ],
    deps = [
        "//base",
    ],
    testonly = 1,
    visibility = [ "//visibility:public" ],
)

cc_test(
    name = "move_only_test",
    srcs = [
        "move_only_test.cc",
    ],
    deps = [
        ":move_only",
        "//third_party/gtest",
    ],
)