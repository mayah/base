cc_library(
    name = "containers",
    srcs = [
    ],
    hdrs = [
        "small_int_set.h",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "containers_test",
    srcs = [
        "small_int_set_test.cc",
    ],
    deps = [
        ":containers",
        "//external:gtest",
        "//third_party:glog",
    ],
)
