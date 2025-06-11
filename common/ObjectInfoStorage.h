#ifndef OBJECT_PATH_STORAGE_H
#define OBJECT_PATH_STORAGE_H

#include <memory>
#include <vector>
#include <sdbus-c++/Types.h>
#include <tuple>
#include "cfgDefines.h"


class ObjectInfoStorage {

public:
    static std::shared_ptr<ObjectInfoStorage> instance() {
        class Proxy : public ObjectInfoStorage {};
        static std::shared_ptr<ObjectInfoStorage> singleInstance = std::make_shared<Proxy>();
        return singleInstance;
    }

    void addDbusConfiguration(const sdbus::ObjectPath& objPath, const FileConfiguration& fileConfig);
    
    const DbusObjectsConfigurations& getStorageData();

private:
    ObjectInfoStorage() = default;
    DbusObjectsConfigurations m_objectData;

};




#endif