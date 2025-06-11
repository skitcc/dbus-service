src = [
    'DbusObjectBuilder.cpp',
    'ServiceBuilder.cpp',
    'ServiceDirector.cpp',
]


deps = [
    common_core_dep,
    reader_core_dep,
    dbusObjects_core_dep,
]

builder_core = static_library(
    'builder-core',
    src,
    dependencies: deps,
    include_directories: ['../../', '../'],
)

builder_core_dep = declare_dependency(
    link_with: builder_core,
    include_directories: ['.', '../../', '../'],
)