cc_library(
    name = "socket",
    srcs = [
        "socket.cc",
        "socket_factory.cc",
        "tcp_client_socket.cc",
        "tcp_server_socket.cc",
        "tcp_socket.cc",
        "unix_domain_client_socket.cc",
        "unix_domain_server_socket.cc",
        "unix_domain_socket.cc",
    ],
    hdrs = [
        "socket.h",
        "socket_descriptor.h",
        "socket_factory.h",
        "tcp_client_socket.h",
        "tcp_server_socket.h",
        "tcp_socket.h",
        "unix_domain_client_socket.h",
        "unix_domain_server_socket.h",
        "unix_domain_socket.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//base",
        "//third_party/glog",
    ],
)
