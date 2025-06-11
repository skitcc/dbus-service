subdir('dbus-objects')
subdir('cfgRead')
subdir('cfgBuilder')
subdir('service')
subdir('serviceManager')



daemon_deps = [
    dbusObjects_core_dep,
    reader_core_dep,
    builder_core_dep,
    manager_core_dep,
    service_core_dep,
]

daemon_core_dep = declare_dependency(
    dependencies: daemon_deps,
    include_directories: ['.', '../'],
)