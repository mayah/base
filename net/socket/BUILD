cc_library(
    name = "socket",
    srcs = [
        "tcp_socket.cc",
        "socket.cc",
        "socket_factory.cc",
        "unix_domain_socket.cc",
    ],
    hdrs = [
        "tcp_socket.h",
        "socket.h",
        "socket_descriptor.h",
        "socket_factory.h",
        "unix_domain_socket.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//base",
        "//third_party:glog",
    ],
)
