#include "ServiceManager.h"
#include <iostream>

ServiceManager::ServiceManager()
{
    m_serviceBuilder = std::make_shared<ServiceBuilder>();
    m_service = std::make_shared<Service>();
}

void ServiceManager::runApplication()
{
    if (!ServiceDirector::create(m_serviceBuilder)) {
        return;
    }
    auto configuratedObjects = m_serviceBuilder->getConfiguratedObjects();

    m_service->addConfiguratedObjects(std::move(configuratedObjects));
    m_service->run();
}