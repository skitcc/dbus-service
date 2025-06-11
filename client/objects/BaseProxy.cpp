#include "BaseProxy.h"


BaseProxy::BaseProxy(sdbus::ServiceName serviceName, sdbus::ObjectPath objectPath)
    : ProxyInterfaces(std::move(serviceName), std::move(objectPath))
{
    registerProxy();    
}


void BaseProxy::onConfigurationChanged(const std::map<std::string, sdbus::Variant>& configuration) {
    
}


BaseProxy::~BaseProxy() {
    unregisterProxy();
}