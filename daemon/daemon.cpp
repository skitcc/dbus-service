#include "serviceManager/ServiceManager.h"

int main()
{
    std::unique_ptr<ServiceManager> serviceManager = std::make_unique<ServiceManager>();
    serviceManager->runApplication();
}