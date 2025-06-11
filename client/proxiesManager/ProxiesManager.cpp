#include "ProxiesManager.h"
#include "proxiesBuilder/ProxiesDirector.h"

ProxiesManager::ProxiesManager() {
    m_proxiesBuilder = std::make_shared<ProxiesBuilder>();
    m_compositeProxies = std::make_shared<ProxyComposite>();
}


void ProxiesManager::runApplication() {
    if (!ProxiesDirector::create(m_proxiesBuilder))
        return;
    
    const auto& configurations = m_proxiesBuilder->getProxiesConfigurations();
    m_compositeProxies->setProxiesConfigurations(configurations);
    m_compositeProxies->run();
}