#include "BaseProxy.h"
#include <iostream>

BaseProxy::BaseProxy(sdbus::IConnection& connection, sdbus::ServiceName serviceName, sdbus::ObjectPath objectPath)
    : ProxyInterfaces(connection, std::move(serviceName), std::move(objectPath))
{
    registerProxy();  
    initConfiguration();  
}

std::optional<FileConfiguration> BaseProxy::convertDbusToStl(const std::map<std::string, sdbus::Variant>& configuration) {
    FileConfiguration currentConf;
    for (const auto& [key, value] : configuration) {
        if (value.containsValueOfType<int>()) {
            currentConf[key] = value.get<int>();
        }
        else if (value.containsValueOfType<std::string>()) {
            currentConf[key] = value.get<std::string>();
        }
        else
            return std::nullopt;
        
    }
    return currentConf;
}

void BaseProxy::initConfiguration() {
    try {
        auto configuration = GetConfiguration();
        auto stlConfiguration = convertDbusToStl(configuration);
        if (!stlConfiguration.has_value())
            throw sdbus::Error(sdbus::Error::Name("Ошибка"), "Неизвестный тип!");
    
        m_conf = stlConfiguration.value();
    } catch(const sdbus::Error& ex) {
        std::cout << ex.what();
    }
} 


void BaseProxy::onConfigurationChanged(const std::map<std::string, sdbus::Variant>& configuration) {

    auto currentConf = convertDbusToStl(configuration);
    if (!currentConf.has_value())
        throw sdbus::Error(sdbus::Error::Name("Ошибка"), "Неизвестный тип!");
    
    m_conf = currentConf.value();

}


BaseProxy::~BaseProxy() {
    unregisterProxy();
}