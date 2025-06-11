src = [
    'ProxiesBuilder.cpp',
    'ProxiesDirector.cpp',
]


deps = [
    common_core_dep,
    reader_core_dep,
]

proxy_builder_core = static_library(
    'proxy_builder-core',
    src,
    dependencies: deps,
    include_directories: ['../../', '../'],
)

proxy_builder_core_dep = declare_dependency(
    link_with: proxy_builder_core,
    include_directories: ['.', '../../'],
)