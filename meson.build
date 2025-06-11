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
boost_dep = dependency('boost', modules: ['json'])

subdir('common')  
subdir('daemon')  
subdir('client')

daemon_deps = [
    sdbus_dep, 
    boost_dep,
    common_core_dep, 
    daemon_core_dep,
]

daemon_src = [
    'daemon/daemon.cpp',
]

executable(
    'daemon.exe',
    daemon_src,
    dependencies: daemon_deps,
    include_directories: ['common', 'daemon'],
    install: true,
)


client_deps = [
    sdbus_dep,
    boost_dep,
    common_core_dep,
    client_core_dep,
]

client_src = [
    'client/client.cpp',
]

executable(
    'client.exe',
    client_src,
    dependencies: client_deps,
    include_directories: ['common', 'client'],
    install: true,
)