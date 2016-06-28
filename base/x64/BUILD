cc_library(
    name = "x64",
    hdrs = [
        "avx.h",
        "bmi.h",
        "sse.h",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "bmi_test",
    srcs = [
        "bmi_test.cc",
    ],
    copts = [
        "-mavx",
    ],
    deps = [
        ":x64",
        "//third_party/gtest",
    ],
)

cc_test(
    name = "sse_test",
    srcs = [
        "sse_test.cc",
    ],
    copts = [
        "-msse4.2",
    ],
    deps = [
        ":x64",
        "//third_party/gtest",
    ],
)
