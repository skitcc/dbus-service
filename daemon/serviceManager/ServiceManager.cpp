#include "ServiceManager.h"
#include <iostream>

ServiceManager::ServiceManager() {
    m_serviceBuilder = std::make_shared<ServiceBuilder>();
}

void ServiceManager::runApplication() {
    if (!ServiceDirector::create(m_serviceBuilder)) {
        return;
    }

    sdbus::IConnection& service = m_serviceBuilder->getConnection();
    service.enterEventLoop();
}