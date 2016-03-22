cc_library(
    name = "base",
    srcs = [
    ],
    hdrs = [
        "build_config.h",
        "compiler_specific.h",
        "macros.h",
        "unit.h",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "macros",
    srcs = [
        "macros_test.cc",
    ],
    deps = [
        ":base",
        "//external:gtest",
        "//third_party:glog",
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
