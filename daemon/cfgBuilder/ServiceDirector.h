#ifndef SERVICE_DIRECTOR_H
#define SERVICE_DIRECTOR_H


#include "ServiceBuilder.h"

class ServiceDirector {
public:
    static bool create(std::shared_ptr<ServiceBuilder> serviceBuilder);

};


#endif