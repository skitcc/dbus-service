#ifndef SERVICE_H
#define SERVICE_H

#include "common/ObjectInfoStorage.h"
#include "common/cfgDefines.h"
#include "dbus-objects/BaseDbusObject.h"
#include <memory>
#include <sdbus-c++/IConnection.h>
#include <sdbus-c++/Types.h>

class Service
{
public:
    Service();

    void run();
    void addConfiguratedObjects(std::vector<std::shared_ptr<BaseDbusObject>> &&configuratedObjects);

private:
    void registrateObjects();

    std::unique_ptr<sdbus::IConnection> m_connection;
    std::vector<std::shared_ptr<BaseDbusObject>> m_objects;

    cfgType m_configType;
    std::map<cfgType,
             std::function<std::shared_ptr<BaseDbusObject>(sdbus::IConnection &, sdbus::ObjectPath)>>
        m_relTypes;
};

#endif