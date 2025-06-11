src = [
    'PathTypeJsonReader.cpp',
]


deps = [
    common_core_dep,
]

proxy_reader_core = static_library(
    'proxy_reader-core',
    src,
    dependencies: deps,
    include_directories: ['../../'],
)

proxy_reader_core_dep = declare_dependency(
    link_with: proxy_reader_core,
    include_directories: ['.', '../../'],
)