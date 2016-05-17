cc_library(
    name = "concurrent",
    srcs = [
        "executor.cc",
        "wait_group.cc",
    ],
    hdrs = [
        "executor.h",
        "wait_group.h"
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//base",
        "//third_party:gflags",
        "//third_party/glog",
    ],
)
