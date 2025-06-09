#include "Config.h"


const sdbus::ServiceName dbus_daemon::Config::getServiceName() {
    return m_serviceName;
}

const std::string dbus_daemon::Config::getBaseObjectPath() {
    return m_baseObjectPath;
}

const std::string_view dbus_daemon::Config::getConfigurationDir() {
    return m_configurationDir;
}