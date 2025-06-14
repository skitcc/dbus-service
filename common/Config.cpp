#include "Config.h"

const sdbus::ServiceName dbus_daemon::Config::getServiceName()
{
    return m_serviceName;
}

const std::string dbus_daemon::Config::getBaseObjectPath()
{
    return m_baseObjectPath;
}

const std::string_view dbus_daemon::Config::getConfigurationDir()
{
    return m_configurationDir;
}

const std::filesystem::path dbus_daemon::Config::getClientConfigPath()
{
    return m_clientConfigPath;
}

const std::vector<std::string_view> dbus_daemon::Config::getValidKeysForConfigType(
    std::string_view configType)
{
    auto it = m_validKeysByConfigType.find(configType);
    if (it != m_validKeysByConfigType.end()) {
        return it->second;
    }
    return {};
}