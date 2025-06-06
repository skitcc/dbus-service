#ifndef SERVICE_H
#define SERVICE_H

#include <filesystem>
#include <sdbus-c++/IConnection.h>
#include "dbus-objects/BaseDbusObject.h"


class Service {
public:
    Service();
    void addObject(std::shared_ptr<BaseDbusObject> dbusObject);
    void run();
    sdbus::IConnection& getConnection();


private:
    std::vector<std::shared_ptr<BaseDbusObject>> m_dbusObjects;
    std::unique_ptr<sdbus::IConnection> m_connection;

};





#endif