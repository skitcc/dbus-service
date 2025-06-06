src = [
    'Service.cpp',
]

deps = [
    dbusObjects_core_dep,
]


service_core = static_library(
    'service-core',
    src,
    dependencies: deps,
    include_directories: ['../'],
)

service_core_dep = declare_dependency(
    link_with: service_core,
    include_directories: ['./', '../'],
)