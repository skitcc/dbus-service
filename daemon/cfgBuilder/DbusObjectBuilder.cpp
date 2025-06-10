#include "DbusObjectBuilder.h"
#include <iostream>


void DbusObjectBuilder::setBuilderParams(std::shared_ptr<BaseReader> reader) {
    m_reader = reader;
}


void DbusObjectBuilder::build() {
    std::map<VariantKey, VariantValue> currentConfig;
    auto field = m_reader->nextField();
    while (field.has_value()) {
        currentConfig[field->first] = field->second;
        field = m_reader->nextField();
    }
    m_builtConfig = std::move(currentConfig);
}

 
std::map<typename DbusObjectBuilder::VariantKey, typename DbusObjectBuilder::VariantValue> DbusObjectBuilder::getBuiltConfig() {
    build();
    return m_builtConfig;
}