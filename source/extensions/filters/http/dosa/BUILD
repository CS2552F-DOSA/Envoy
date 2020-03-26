licenses(["notice"]) 

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_extension(
    name = "config",
    srcs = ["http_filter_config.cc"],
    security_posture = "robust_to_untrusted_downstream",
    deps = [
        ":dosa_filter_lib",
        "//include/envoy/registry",
        "//include/envoy/server:filter_config_interface",
        "//source/extensions/filters/http:well_known_names",
        "//source/extensions/filters/http/common:factory_base_lib",
        "@envoy_api//envoy/extensions/filters/network/echo/v3:pkg_cc_proto",
    ],
)

envoy_cc_library(
    name = "dosa_filter_lib",
    srcs = ["http_filter.cc"],
    hdrs = ["http_filter.h"],
    repository = "@envoy",
    deps = [
        "//include/envoy/http:filter_interface",
        "//include/envoy/stats:stats_macros",
        "//source/common/http:utility_lib",
        "//source/extensions/filters/http:well_known_names",
        "//include/envoy/buffer:buffer_interface",
        "//include/envoy/network:connection_interface",
        "//include/envoy/network:filter_interface",
        "//source/common/common:assert_lib",
        "//source/common/common:minimal_logger_lib",
    ],
)