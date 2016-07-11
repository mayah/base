cc_binary(
    name = "fork_perf",
    srcs = [
        "fork_perf.cc",
    ],
    deps = [
        "//base/time",
        "//third_party/gflags",
    ],
)

cc_binary(
    name = "tcp_echo",
    srcs = [
        "tcp_echo.cc",
    ],
    deps = [
        "//net/socket",
        "//third_party/gflags",
    ],
)

cc_binary(
    name = "tcp_echo_client",
    srcs = [
        "tcp_echo_client.cc",
    ],
    deps = [
        "//base/time",
        "//net/socket",
        "//third_party/gflags",
    ],
)

cc_binary(
    name = "eigen_blas",
    srcs = [
        "eigen_blas.cc",
    ],
    linkopts = [
        "-lopenblas",
    ],
    deps = [
        "//base/time",
    ],
)
