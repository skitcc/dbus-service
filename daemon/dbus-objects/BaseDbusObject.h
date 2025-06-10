#ifndef BASE_DBUS_OBJECT_H
#define BASE_DBUS_OBJECT_H


#include "adapters/ConfigurationAdapter.h"
#include <sdbus-c++/AdaptorInterfaces.h>
#include "common/cfgDefines.h"


class BaseDbusObject : public sdbus::AdaptorInterfaces<com::system::configurationManager::Application::Configuration_adaptor> {
    using VariantKey = std::string;
    using VariantValue = std::variant<int, std::string>;

public:
    BaseDbusObject() = default;
    BaseDbusObject(sdbus::IConnection& connection, sdbus::ObjectPath objectPath);

    void setConfiguration(const FileConfiguration& conf);
    virtual void specificBehaviour() = 0;
    virtual ~BaseDbusObject();
    
protected:
    void ChangeConfiguration(const std::string& key, const sdbus::Variant& value) override;
    std::map<std::string, sdbus::Variant> GetConfiguration() override;
    FileConfiguration m_conf;

};




#endif