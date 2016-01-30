cc_library(
    name = "file",
    srcs = [
        "file.cc",
        "path.cc",
        "scoped_temp_dir.cc",
        "scoped_temp_file.cc",
    ],
    hdrs = [
        "file.h",
        "path.h",
        "scoped_temp_dir.h",
        "scoped_temp_file.h",
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
