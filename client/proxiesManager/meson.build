src = [
    'ProxiesManager.cpp',
]


deps = [
    proxy_builder_core_dep,
    proxy_composite_core_dep,
]

proxy_manager_core = static_library(
    'proxy_manager-core',
    src,
    dependencies: deps,
    include_directories: ['../../', '../'],
)

proxy_manager_core_dep = declare_dependency(
    link_with: proxy_manager_core,
    include_directories: ['.', '../../'],
)