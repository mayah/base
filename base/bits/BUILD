cc_library(
    name = "bits",
    hdrs = [
        "count.h",
    ],
    visibility = [ "//visibility:public" ],
)

cc_test(
    name = "count_test",
    size = "small",
    srcs = [
        "count_test.cc",
    ],
    deps = [
        ":bits",
        "//third_party/gtest"
    ],
)
