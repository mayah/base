cc_library(
    name = "base",
    srcs = [
    ],
    hdrs = [
        "macros.h",
        "unit.h",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "unit_test",
    srcs = [
        "unit_test.cc",
    ],
    deps = [
        ":base",
        "//external:gtest",
        "//third_party:glog",
    ],
)
