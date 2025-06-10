#include "ObjectInfoStorage.h"


void ObjectInfoStorage::addDbusConfiguration(const sdbus::ObjectPath& objPath, const cfgType type, const FileConfiguration& fileConfig) {
    m_objectData.push_back(std::make_tuple(objPath, type, fileConfig));
}


const DbusObjectsConfigurations& ObjectInfoStorage::getStorageData() {
    return m_objectData;
}