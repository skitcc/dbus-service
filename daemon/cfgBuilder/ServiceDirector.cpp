#include "ServiceDirector.h"
#include <iostream>

bool ServiceDirector::create(std::shared_ptr<ServiceBuilder> serviceBuilder)
{
    return serviceBuilder->build();
}