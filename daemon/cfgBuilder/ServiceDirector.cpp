#include "ServiceDirector.h"
#include <iostream>

bool ServiceDirector::create(std::shared_ptr<ServiceBuilder> serviceBuilder) {
    if (serviceBuilder->build()) {
        return true;
    }
    return false;
}