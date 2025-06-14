#ifndef BASE_DBUS_OBJECT_H
#define BASE_DBUS_OBJECT_H

#include "adapters/ConfigurationAdapter.h"
#include "common/cfgDefines.h"
#include <sdbus-c++/AdaptorInterfaces.h>

class BaseDbusObject: public sdbus::AdaptorInterfaces<
                          com::system::configurationManager::Application::Configuration_adaptor>
{
    using VariantKey = std::string;
    using VariantValue = std::variant<int, std::string>;

public:
    BaseDbusObject(sdbus::IConnection &connection, sdbus::ObjectPath objectPath);

    void setConfiguration(const FileConfiguration &conf);
    ~BaseDbusObject();

private:
    void ChangeConfiguration(const std::string &key, const sdbus::Variant &value) override;
    void stlToDbus(std::map<std::string, sdbus::Variant> &result);
    std::map<std::string, sdbus::Variant> GetConfiguration() override;
    FileConfiguration m_conf;
};

#endif