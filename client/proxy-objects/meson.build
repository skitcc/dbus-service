src = [
    'BaseProxy.cpp',
    'TimeoutProxy.cpp',
]


deps = [
    common_core_dep,
]

proxy_objects_core = static_library(
    'proxy_objects-core',
    src,
    dependencies: deps,
    include_directories: ['../../'],
)

proxy_objects_core_dep = declare_dependency(
    link_with: proxy_objects_core,
    include_directories: ['.', '../../'],
)