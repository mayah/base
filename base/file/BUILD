cc_library(
    name = "file",
    srcs = [
        "file.cc",
        "path.cc",
    ],
    hdrs = [
        "file.h",
        "path.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//base/strings",
    ],
)

cc_test(
    name = "path_test",
    srcs = [
        "path_test.cc",
    ],
    deps = [
        ":file",
        "//external:gtest",
        "//third_party:glog",
    ],
)
