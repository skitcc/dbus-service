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

subdir('cfgRead')



src = [
    'main.cpp',
]

deps = [
    sdbus_dep,
    reader_core_dep,
]


executable(
    'app.exe',
    src,
    dependencies: deps,
    install: true,
)