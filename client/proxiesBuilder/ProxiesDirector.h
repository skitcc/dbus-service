#ifndef PROXIES_DIRECTOR_H
#define PROXIES_DIRECTOR_H

#include "ProxiesBuilder.h"
#include <memory>

class ProxiesDirector {
public:
    static bool create(std::shared_ptr<ProxiesBuilder> builder);
};



#endif