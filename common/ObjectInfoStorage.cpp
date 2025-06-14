#include "ObjectInfoStorage.h"

void ObjectInfoStorage::addDbusConfiguration(const sdbus::ObjectPath &objPath,
                                             const FileConfiguration &fileConfig,
                                             const std::string &cfgType)
{
    m_objectData.push_back(std::make_tuple(objPath, fileConfig, cfgType));
}

const DbusObjectsConfigurations &ObjectInfoStorage::getStorageData()
{
    return m_objectData;
}