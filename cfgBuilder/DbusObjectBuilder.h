#ifndef BASE_BUILDER_H
#define BASE_BUILDER_H

#include "cfgRead/ConcreteReader.h"
#include "dbus-objects/TimeoutObject.h"
#include "exceptions/Exceptions.h"

#include <memory>
#include <functional>
#include <sdbus-c++/Types.h>


class BaseDbusObjectBuilder {
protected:
    using VariantKey = std::string;
    using VariantValue = std::variant<int, std::string>;

    using Field = std::pair<VariantKey, VariantValue>;

public:
    BaseDbusObjectBuilder() = default;

    virtual ~BaseDbusObjectBuilder() = default;
    virtual void setBuilderParams(std::shared_ptr<BaseReader> reader, cfgType configType) = 0;
    virtual void setObjectAttributes(sdbus::IConnection& connection, sdbus::ObjectPath path) = 0;
    virtual std::shared_ptr<BaseDbusObject> getBuildedObject() = 0;

protected:
    std::shared_ptr<BaseReader> m_reader;
    std::shared_ptr<BaseDbusObject> m_object;
    cfgType m_configType;

    std::map<cfgType, std::function<std::shared_ptr<BaseDbusObject>(sdbus::IConnection&, sdbus::ObjectPath)>> m_relTypes;
    virtual void build() = 0;

};

class DbusObjectBuilder : public BaseDbusObjectBuilder {
public:
    DbusObjectBuilder();
    void setBuilderParams(std::shared_ptr<BaseReader> reader, cfgType configType) override;
    virtual void setObjectAttributes(sdbus::IConnection& connection, sdbus::ObjectPath path) override;

    std::shared_ptr<BaseDbusObject> getBuildedObject() override;

protected:
    void build() override;

};





#endif