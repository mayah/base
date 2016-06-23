cc_library(
    name = "time",
    srcs = [
        "clock.cc",
        "current_time.cc",
        "fake_clock.cc",
        "lap_timer.cc",
        "time.cc",
        "time_stamp_counter.cc",
    ],
    hdrs = [
        "clock.h",
        "current_time.h",
        "fake_clock.h",
        "lap_timer.h",
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
    size = "small",
    srcs = [
        "fake_clock_test.cc",
    ],
    deps = [
        ":time",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)

cc_test(
    name = "time_test",
    size = "small",
    srcs = [
        "time_test.cc",
    ],
    deps = [
        ":time",
        "//third_party/gtest",
        "//third_party/glog",
    ],
)
