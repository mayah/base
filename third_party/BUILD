cc_library(
    name = "gflags",
    linkopts = select({
        "//config:darwin": ["-headerpad_max_install_names"],
        "//conditions:default": [],
    }),
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//external:gflags",
    ],
)
