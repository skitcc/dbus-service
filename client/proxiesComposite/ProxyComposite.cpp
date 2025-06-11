#include "ProxyComposite.h"
#include "common/Exceptions.h"
#include "common/Config.h"


ProxyComposite::ProxyComposite() {
    m_connection = sdbus::createSessionBusConnection();

    m_relations = {
        {cfgType::TIMEOUT, [](sdbus::IConnection& connection,sdbus::ServiceName serviceName,sdbus::ObjectPath path){
            return std::make_shared<TimeoutProxy>(connection, serviceName, path);
        }},
    };
}

void ProxyComposite::setProxiesConfigurations(const std::vector<ClientConfiguration>& configurations) {
    m_clientConfigurations = configurations;

}


void ProxyComposite::registrateProxies() {
    for (const auto& [objectPath, type] : m_clientConfigurations) {
        auto it = m_relations.find(type);
        if (it == m_relations.end())
            throw UnsupportedConfiguration(__FILE__, typeid(ProxyComposite).name(), __FUNCTION__);
        auto proxyObject = it->second(*m_connection, dbus_daemon::Config::getServiceName(), objectPath);
        m_proxies.push_back(proxyObject);
    }
}

void ProxyComposite::run() {
    registrateProxies();
    for (const auto& proxy : m_proxies) {
        proxy->specificBehaviour();
    }
    m_connection->enterEventLoop();
}