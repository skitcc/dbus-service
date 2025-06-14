#ifndef PROXY_COMPOSITE_H
#define PROXY_COMPOSITE_H

#include "common/cfgDefines.h"
#include "proxy-objects/TimeoutProxy.h"
#include <functional>
#include <sdbus-c++/IConnection.h>

class ProxyComposite
{
public:
    ProxyComposite();

    void registrateProxies();
    void run();
    void setProxiesConfigurations(const std::vector<ClientConfiguration> &configurations);

private:
    std::map<cfgType,
             std::function<std::shared_ptr<BaseProxy>(
                 sdbus::IConnection &, sdbus::ServiceName, sdbus::ObjectPath)>>
        m_relations;
    std::vector<ClientConfiguration> m_clientConfigurations;
    std::vector<std::shared_ptr<BaseProxy>> m_proxies;
    std::unique_ptr<sdbus::IConnection> m_connection;
};

#endif