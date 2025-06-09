#ifndef BASE_PROXY_H
#define BASE_PROXY_H

#include "proxies/configurationProxy.h"
#include <sdbus-c++/ProxyInterfaces.h>

class BaseProxy : public sdbus::ProxyInterfaces<com::system::configurationManager::Application::Configuration_proxy>{
public:
    BaseProxy(sdbus::ServiceName serviceName, sdbus::ObjectPath objectPath);

    virtual void onConfigurationChanged(const std::map<std::string, sdbus::Variant>& configuration) = 0;
    
    virtual ~BaseProxy();

};




#endif