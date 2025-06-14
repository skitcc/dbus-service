#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <sdbus-c++/Types.h>
#include <string>

namespace dbus_daemon {

class Config
{
public:
    static const sdbus::ServiceName getServiceName();
    static const std::string getBaseObjectPath();
    static const std::string_view getConfigurationDir();
    static const std::filesystem::path getClientConfigPath();
    static const std::vector<std::string_view> getValidKeysForConfigType(std::string_view configType);

private:
    static const inline sdbus::ServiceName m_serviceName{"com.system.configurationManager"};
    static const inline std::string m_baseObjectPath{
        "/com/system/configurationManager/Application"};
    static const inline std::string_view m_configurationDir{"../data/"};
    static const inline std::filesystem::path m_clientConfigPath{
        "../client_settings/settings.json"};

    static const inline std::unordered_map<std::string_view, std::vector<std::string_view>>
        m_validKeysByConfigType{{"Timeout", {"Timeout", "TimeoutPhrase"}}};
};

}

#endif