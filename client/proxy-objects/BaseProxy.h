#ifndef BASE_PROXY_H
#define BASE_PROXY_H

#include "adapters/configurationProxy.h"
#include "common/cfgDefines.h"
#include <mutex>
#include <sdbus-c++/ProxyInterfaces.h>

class BaseProxy: public sdbus::ProxyInterfaces<
                     com::system::configurationManager::Application::Configuration_proxy>
{
public:
    BaseProxy(sdbus::IConnection &connection,
              sdbus::ServiceName serviceName,
              sdbus::ObjectPath objectPath);

    void onConfigurationChanged(const std::map<std::string, sdbus::Variant> &configuration) override;
    virtual void specificBehaviour() = 0;
    virtual ~BaseProxy();

protected:
    FileConfiguration m_conf;
    std::mutex m_confMutex;

private:
    void initConfiguration();

    std::optional<FileConfiguration> convertDbusToStl(
        const std::map<std::string, sdbus::Variant> &configuration);
};

#endif