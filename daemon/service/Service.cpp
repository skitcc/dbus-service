#include "Service.h"

#include "common/Config.h"
#include "common/Exceptions.h"
#include <iostream>

Service::Service()
{
    try {
        m_connection = sdbus::createSessionBusConnection();
        m_connection->requestName(dbus_daemon::Config::getServiceName());
    }
    catch (const sdbus::Error &ex) {
        std::cout
            << "Raised exception while asking for well kwown name or creating a bus connection! : "
            << ex.what();
    }
}

void Service::addConfiguratedObjects(
    std::vector<std::shared_ptr<BaseDbusObject>> &&configuratedObjects)
{
    m_objects = configuratedObjects;
}

void Service::registrateObjects()
{
    auto storage = ObjectInfoStorage::instance();
    auto &storageData = storage->getStorageData();

    for (auto &dataIt: storageData) {
        const auto validKeys = dbus_daemon::Config::getValidKeysForConfigType(
            std::get<std::string>(dataIt));

        if (validKeys.empty()) {
            throw UnsupportedConfiguration(__FILE__, typeid(*this).name(), __FUNCTION__, __LINE__);
        }

        for (const auto &[key, _]: std::get<FileConfiguration>(dataIt)) {
            if (std::none_of(validKeys.begin(), validKeys.end(), [&key](std::string_view validKey) {
                return validKey == key;
            })) {
                throw UnsupportedKeyConfiguration(__FILE__,
                                                  typeid(*this).name(),
                                                  __FUNCTION__,
                                                  __LINE__);
            }
        }
        std::shared_ptr<BaseDbusObject> object
            = std::make_shared<BaseDbusObject>(*m_connection, std::get<sdbus::ObjectPath>(dataIt));

        object->setConfiguration(std::get<FileConfiguration>(dataIt));
        m_objects.push_back(object);
    }
}

void Service::run()
{
    registrateObjects();
    try {
        std::cout << "Service is running...\n";
        m_connection->enterEventLoop();
    }
    catch (const sdbus::Error &ex) {
        std::cout << "Raised exception while trying to join the event loop! : " << ex.what();
    }
}