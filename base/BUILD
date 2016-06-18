cc_library(
    name = "base",
    srcs = [
    ],
    hdrs = [
        "build_config.h",
        "compiler_specific.h",
        "machine_info.h",
        "macros.h",
        "memory.h",
        "unit.h",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "machine_info",
    srcs = [
        "machine_info.cc",
    ],
    hdrs = [
        "machine_info.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//base/file",
        "//third_party/glog",
    ],
)

cc_test(
    name = "macros",
    srcs = [
        "macros_test.cc",
    ],
    deps = [
        ":base",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "memory_test",
    srcs = [
        "memory_test.cc",
    ],
    deps = [
        ":base",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "unit_test",
    srcs = [
        "unit_test.cc",
    ],
    deps = [
        ":base",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)
