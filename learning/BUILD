cc_library(
    name = "multi_layer_perceptron",
    hdrs = [
        "multi_layer_perceptron.h",
    ],
    srcs = [
        "multi_layer_perceptron.cc",
    ],
    deps = [
        "//base/file",
        "//math",
    ],
    linkopts = [
        "-lm",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "arow",
    hdrs = [
        "arow.h",
    ],
    srcs = [
        "arow.cc",
    ],
    deps = [
        "//base/file",
    ],
    linkopts = [
        "-lm",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "multi_layer_perceptron_test",
    srcs = [
        "multi_layer_perceptron_test.cc"
    ],
    deps = [
        ":multi_layer_perceptron",
        "//third_party/gtest",
    ],
)

cc_test(
    name = "arow_test",
    srcs = [
        "arow_test.cc"
    ],
    deps = [
        ":arow",
        "//third_party/gtest",
    ],
)
