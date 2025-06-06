#include "ServiceManager.h"
#include <iostream>

ServiceManager::ServiceManager() {
    m_serviceBuilder = std::make_shared<ServiceBuilder>();
}

void ServiceManager::runApplication() {

    if (!ServiceDirector::create(m_serviceBuilder)) {
        std::cout << "in wrong condition!\n";
        return;
    }

    std::shared_ptr<Service> service = m_serviceBuilder->getService();
    service->run();
}