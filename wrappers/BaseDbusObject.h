#ifndef BASE_DBUS_OBJECT_H
#define BASE_DBUS_OBJECT_H

#include <sdbus-c++/IObject.h>
#include <memory>
#include "objectStrategies/BaseObjectStrategy.h"

class BaseDbusObject : public sdbus::IObject {
protected:
    using Variant = std::optional<std::variant<int, std::string>>;
public:

    virtual ~BaseDbusObject() = default;

    void setConfiguration(std::map<std::string, Variant>&& conf) {
        m_conf = conf;
    };


protected:

    std::unique_ptr<BaseObjectStrategy> m_methods;
    std::map<std::string, Variant> m_conf;


};




#endif