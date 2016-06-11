cc_library(
    name = "time",
    srcs = [
        "clock.cc",
        "current_time.cc",
        "fake_clock.cc",
        "time.cc",
        "time_stamp_counter.cc",
    ],
    hdrs = [
        "clock.h",
        "current_time.h",
        "fake_clock.h",
        "scoped_time.h",
        "time.h",
        "time_stamp_counter.h",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "fake_clock_test",
    srcs = [
        "fake_clock_test.cc",
    ],
    deps = [
        ":time",
        "//external:gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "time_test",
    srcs = [
        "time_test.cc",
    ],
    deps = [
        ":time",
        "//external:gtest",
        "//third_party/glog",
    ],
)
