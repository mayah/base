cc_library(
    name = "glog",
    hdrs = [
        "glog/logging.h",
        "glog/log_severity.h",
        "glog/raw_logging.h",
        "glog/stl_logging.h",
        "glog/vlog_is_on.h",
    ],
    deps = [":glog_impl"],
    includes = ["."],
    visibility = ["//visibility:public"],
    licenses = ["notice"],
)

cc_library(
    name = "glog_impl",
    srcs = [
        "impl/demangle.cc",
        "impl/logging.cc",
        "impl/raw_logging.cc",
        "impl/signalhandler.cc",
        "impl/symbolize.cc",
        "impl/utilities.cc",
        "impl/vlog_is_on.cc",
    ],
    hdrs = glob(["impl/*.h", "impl/base/*.h", "glog/*.h"]),
    deps = [
        "//base",
        "//third_party:gflags",
    ],
    linkopts = [
        "-pthread"
    ],
    copts = [
        "-Ithird_party/glog"
    ],
    licenses = ["notice"],
    visibility = ["//visibility:private"],
)
