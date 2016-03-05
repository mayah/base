cc_binary(
    name = "read_file",
    srcs = ["read_file.cc"],
    deps = ["//base/file"],
)

cc_binary(
    name = "write_file",
    srcs = ["write_file.cc"],
    deps = ["//base/file"],
)

cc_binary(
    name = "rm_tree",
    srcs = [
        "rm_tree.cc"
    ],
    deps = [
        "//base/file",
        "//base/strings",
        "//third_party:glog",
    ],
)

cc_binary(
    name = "current_time",
    srcs = [
        "current_time.cc",
    ],
    deps = [
        "//base/time",
    ],
)

cc_binary(
    name = "scoped_temp_dir",
    srcs = [
        "scoped_temp_dir.cc"
    ],
    deps = [
        "//base/file",
        "//third_party:glog",
    ],
)

cc_binary(
    name = "scoped_temp_file",
    srcs = [
        "scoped_temp_file.cc"
    ],
    deps = [
        "//base/file",
        "//third_party:glog",
    ],
)

cc_binary(
    name = "unix_domain_socket_client",
    srcs = [
        "unix_domain_socket_client.cc"
    ],
    deps = [
        "//base/time",
        "//net/socket",
        "//third_party:glog",
    ],
)

cc_binary(
    name = "unix_domain_socket_server",
    srcs = [
        "unix_domain_socket_server.cc"
    ],
    deps = [
        "//net/socket",
        "//third_party:glog",
    ],
)
