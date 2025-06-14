#include "ServiceDirector.h"
#include <iostream>

bool ServiceDirector::create(std::shared_ptr<ServiceBuilder> serviceBuilder)
{
    bool res;
    try {
        res = serviceBuilder->build();
    }
    catch (const BaseException &ex) {
        ex.what();
    }
    return res;
}