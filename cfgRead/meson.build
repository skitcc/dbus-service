src = [
    'ConcreteReader.cpp',
    'ReaderFactory.cpp',
]

deps = [
    exceptions_core_dep,
]


reader_core = static_library(
    'reader-core',
    src,
    dependencies: deps,
    include_directories: ['../'],
)

reader_core_dep = declare_dependency(
    link_with: reader_core,
    include_directories: ['./', '../'],
)