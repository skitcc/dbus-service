#include "BaseDbusObject.h"
#include "common/Exceptions.h"


BaseDbusObject::BaseDbusObject(sdbus::IConnection& connection, sdbus::ObjectPath objectPath) 
    : AdaptorInterfaces(connection, std::move(objectPath)) 
{
    registerAdaptor();
}


void BaseDbusObject::setConfiguration(const FileConfiguration& conf) {
    m_conf = conf;
}


void BaseDbusObject::ChangeConfiguration(const std::string& key, const sdbus::Variant& value) {
    auto it = m_conf.find(key);
    if (it == m_conf.end()) {
        throw sdbus::Error(sdbus::Error::Name("Configuration params error!"), "Error : no such value by this key!");
    }

    m_conf[key] = value;
}

std::map<std::string, sdbus::Variant> BaseDbusObject::GetConfiguration() {
    std::map<std::string, sdbus::Variant> result;
    
    for (const auto& [key, value] : m_conf) {
        sdbus::Variant variantVal;
        std::visit([&variantVal](const auto& val) {
            variantVal = sdbus::Variant(val);
        }, value);
        result[key] = variantVal;
    }
    emitConfigurationChanged(result);
    return result;
}

BaseDbusObject::~BaseDbusObject() {
    unregisterAdaptor();
}

