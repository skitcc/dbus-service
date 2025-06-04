src = [
    'Exceptions.cpp',
]

exceptions_core = static_library(
    'exceptions-core',
    src,
    include_directories: ['../'],
)

exceptions_core_dep = declare_dependency(
    link_with: exceptions_core,
    include_directories: ['./', '../'],
)