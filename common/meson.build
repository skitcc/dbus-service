src = [
    'Config.cpp',
    'Exceptions.cpp'
]



common_core = static_library(
    'common-core',
    src,
    include_directories: ['.'],
)

common_core_dep = declare_dependency(
    link_with: common_core,
    include_directories: ['.'],
)