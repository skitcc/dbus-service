#include "ObjectInfoStorage.h"


void ObjectInfoStorage::addDbusConfiguration(const sdbus::ObjectPath& objPath, const FileConfiguration& fileConfig) {
    m_objectData.push_back(std::make_pair(objPath, fileConfig));
}


const DbusObjectsConfigurations& ObjectInfoStorage::getStorageData() {
    return m_objectData;
}