#ifndef PROXIES_MANAGER_H
#define PROXIES_MANAGER_H

#include "proxiesBuilder/ProxiesBuilder.h"
#include "proxiesComposite/ProxyComposite.h"

class ProxiesManager
{
public:
    ProxiesManager();

    void runApplication();

private:
    std::shared_ptr<ProxiesBuilder> m_proxiesBuilder;
    std::shared_ptr<ProxyComposite> m_compositeProxies;
};

#endif