#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include "cfgBuilder/ServiceDirector.h"


class ServiceManager {
public:
    ServiceManager();

    void runApplication();

private:
    std::shared_ptr<ServiceBuilder> m_serviceBuilder;
};


#endif