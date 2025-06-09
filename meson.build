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

subdir('common')  
subdir('daemon')  

daemon_src = [
    'daemon/daemon.cpp',
]
executable(
    'daemon.exe',
    daemon_src,
    dependencies: [sdbus_dep, common_core_dep, daemon_core_dep],
    include_directories: ['common', 'daemon'],
    install: true,
)
