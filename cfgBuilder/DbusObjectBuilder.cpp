#include "DbusObjectBuilder.h"
#include <iostream>

DbusObjectBuilder::DbusObjectBuilder() {
    m_relTypes = 
    {
        {cfgType::TIMEOUT, [](sdbus::IConnection& connection, sdbus::ObjectPath path){
            return std::make_shared<TimeoutObject>(connection, path);
        }},
    };
}

void DbusObjectBuilder::setBuilderParams(std::shared_ptr<BaseReader> reader, cfgType configType) {
    m_reader = reader;
    m_configType = configType;
    std::cout << "in set builder params\n";
}

void DbusObjectBuilder::setObjectAttributes(sdbus::IConnection& connection, sdbus::ObjectPath path) {
    auto it = m_relTypes.find(m_configType);
    std::cout << "in attributes\n";

    if (it == m_relTypes.end()) {
        throw UnsupportedConfiguration(__FILE__, typeid(DbusObjectBuilder).name(), __FUNCTION__);
    }
    try {
        m_object = it->second(connection, path);
    } catch(const sdbus::Error& ex) {
        std::cout << ex.what() << '\n';
    }
    
}


void DbusObjectBuilder::build() {
    std::map<VariantKey, VariantValue> currentConfig;
    auto field = m_reader->nextField();
    while (field.has_value()) {
        currentConfig[field->first] = field->second;
        field = m_reader->nextField();
    }

    m_object->setConfiguration(std::move(currentConfig));
}


std::shared_ptr<BaseDbusObject> DbusObjectBuilder::getBuildedObject() {
    build();
    return m_object;
}
