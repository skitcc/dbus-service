subdir('proxy-objects')
subdir('proxyReader')
subdir('proxiesBuilder')
subdir('proxiesComposite')
subdir('proxiesManager')


client_deps = [
    proxy_objects_core_dep,
    proxy_reader_core_dep,
    proxy_builder_core_dep,
    proxy_composite_core_dep,
    proxy_manager_core_dep,
]

client_core_dep = declare_dependency(
    dependencies: client_deps,
    include_directories: ['.', '../'],
)