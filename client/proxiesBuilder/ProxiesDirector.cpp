#include "ProxiesDirector.h"
#include "common/Exceptions.h"

bool ProxiesDirector::create(std::shared_ptr<ProxiesBuilder> builder)
{
    bool res;
    try {
        res = builder->build();
    }
    catch (const BaseException &ex) {
        ex.what();
    }
    return res;
}