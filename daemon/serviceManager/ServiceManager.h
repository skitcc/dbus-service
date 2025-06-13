#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include "cfgBuilder/ServiceDirector.h"
#include "service/Service.h"

class ServiceManager
{
public:
    ServiceManager();

    void runApplication();

private:
    std::shared_ptr<ServiceBuilder> m_serviceBuilder;
    std::shared_ptr<Service> m_service;
};

#endif