cc_library(
    name = "glog",
    hdrs = [
        "glog/log_severity.h",
        "glog/logging.h",
        "glog/raw_logging.h",
        "glog/stl_logging.h",
        "glog/vlog_is_on.h",
    ],
    licenses = ["notice"],
    visibility = ["//visibility:public"],
    deps = [":glog_impl"],
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
    hdrs = glob([
        "impl/*.h",
        "impl/base/*.h",
        "glog/*.h",
    ]),
    copts = [
        "-Ithird_party/glog",
    ],
    licenses = ["notice"],
    linkopts = [
        "-pthread",
    ] + select({
        "//config:linux_x64": ["-lunwind"],
        "//config:linux_x86": ["-lunwind"],
        "//conditions:default": [],
    }),
    visibility = ["//visibility:private"],
    deps = [
        "//base",
        "//third_party/gflags",
    ],
)
