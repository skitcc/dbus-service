src = [
    'BaseDbusObject.cpp',
    'TimeoutObject.cpp',
]

deps = [
    exceptions_core_dep,
]


dbusObjects_core = static_library(
    'dbusObjects-core',
    src,
    dependencies: deps,
    include_directories: ['../'],
)

dbusObjects_core_dep = declare_dependency(
    link_with: dbusObjects_core,
    include_directories: ['./', '../'],
)