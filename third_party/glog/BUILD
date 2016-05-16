cc_library(
    name = "glog",
    hdrs = [
        "glog/logging.h",
        "glog/log_severity.h",
        "glog/raw_logging.h",
        "glog/stl_logging.h",
        "glog/vlog_is_on.h",
    ],
    deps = [
        ":glog_internal",
    ],
    linkopts = [
        "-pthread"
    ],
    visibility = ["//visibility:public"],
    licenses = ["notice"],
)

cc_library(
    name = "glog_internal",
    srcs = [
        "demangle.cc",
        "logging.cc",
        "raw_logging.cc",
        "signalhandler.cc",
        "symbolize.cc",
        "utilities.cc",
        "vlog_is_on.cc",
    ],
    hdrs = glob(["*.h"]) + [
        "base/commandlineflags.h",
        "base/googleinit.h",
        "base/mutex.h",
        "glog/logging.h",
        "glog/log_severity.h",
        "glog/raw_logging.h",
        "glog/stl_logging.h",
        "glog/vlog_is_on.h",
    ],
    deps = [
        "//base",
        "//third_party:gflags",
    ],
    linkopts = [
        "-pthread"
    ],
    includes = ["."],
    licenses = ["notice"],
)
