#include "Service.h"
#include <iostream>


Service::Service() : m_connection(sdbus::createSessionBusConnection()) {
    sdbus::ServiceName serviceName{"com.system.configurationManager"}; 
    try {
        m_connection->requestName(serviceName);
        std::cout << "Service name acquired: com.system.configurationManager\n";
    } catch (const sdbus::Error& e) {
        std::cerr << "Failed to acquire service name: " << e.getName() << " - " << e.getMessage() << "\n";
        throw;
    }
}

void Service::addObject(std::shared_ptr<BaseDbusObject> dbusObject) {
    m_dbusObjects.push_back(dbusObject);
}

std::shared_ptr<sdbus::IConnection> Service::getConnection() {
    return m_connection;
}

void Service::run() {
    std::cout << "in service run!!!\n";
    for (auto& dbusObject : m_dbusObjects) {
        dbusObject->specificBehaviour();
    }

    try {
        m_connection->enterEventLoop();
    } catch (const sdbus::Error& e) {
        std::cout << "DBUS error in event loop: " << e.what() << '\n';
    }
}