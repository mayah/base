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
    includes = [
        "."
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
    hdrs = [
        "config.h",
        "demangle.h",
        "googletest.h",
        "mock-log.h",
        "stacktrace.h",
        "stacktrace_generic-inl.h",
        "stacktrace_libunwind-inl.h",
        "stacktrace_powerpc-inl.h",
        "stacktrace_x86-inl.h",
        "stacktrace_x86_64-inl.h",
        "symbolize.h",
        "utilities.h",
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
    copts = [
        "-Ithird_party/glog"
    ],
    licenses = ["notice"],
)
