project(
    'apm',
    ['c', 'cpp'],
    version: '0.1.0',
    default_options: [
            'cpp_std=c++20',
            'optimization=0', 
    ],
)


sdbus_dep = dependency('sdbus-c++')

subdir('exceptions')
subdir('cfgRead')
subdir('dbus-objects')
subdir('service')
subdir('cfgBuilder')
subdir('serviceManager')


src = [
    'main.cpp',
]

deps = [
    sdbus_dep,
    exceptions_core_dep,
    reader_core_dep,
    dbusObjects_core_dep,
    service_core_dep,
    builder_core_dep,
    manager_core_dep,
]


executable(
    'app.exe',
    src,
    dependencies: deps,
    install: true,
)