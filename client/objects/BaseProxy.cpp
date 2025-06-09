#include "BaseProxy.h"


BaseProxy::BaseProxy(sdbus::ServiceName serviceName, sdbus::ObjectPath objectPath)
    : ProxyInterfaces(std::move(serviceName), std::move(objectPath))
{
    registerProxy();    
}



BaseProxy::~BaseProxy() {
    unregisterProxy();
}