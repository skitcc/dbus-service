#include "ProxiesDirector.h"


bool ProxiesDirector::create(std::shared_ptr<ProxiesBuilder> builder) {
    return builder->build();
}