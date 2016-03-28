cc_library(
    name = "multi_layer_perceptron",
    hdrs = [
        "multi_layer_perceptron.h",
    ],
    srcs = [
        "multi_layer_perceptron.cc",
    ],
    deps = [
        "//math",
    ],
)

cc_test(
    name = "multi_layer_perceptron_test",
    srcs = [
        "multi_layer_perceptron_test.cc"
    ],
    deps = [
        ":multi_layer_perceptron",
        "//external:gtest",
    ],
)
