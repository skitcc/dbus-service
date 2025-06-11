src = [
    'ProxyComposite.cpp',
]


deps = [
    common_core_dep,
    proxy_objects_core_dep,
]

proxy_composite_core = static_library(
    'proxy_composite-core',
    src,
    dependencies: deps,
    include_directories: ['../../', '../'],
)

proxy_composite_core_dep = declare_dependency(
    link_with: proxy_composite_core,
    include_directories: ['.', '../../'],
)