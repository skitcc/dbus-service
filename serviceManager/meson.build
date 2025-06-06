src = [
    'ServiceManager.cpp',
]

deps = [
    builder_core_dep,
]


manager_core = static_library(
    'manager-core',
    src,
    dependencies: deps,
    include_directories: ['../'],
)

manager_core_dep = declare_dependency(
    link_with: manager_core,
    include_directories: ['./', '../'],
)