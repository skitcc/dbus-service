#ifndef BASE_BUILDER_H
#define BASE_BUILDER_H

#include "cfgRead/ConcreteReader.h"
#include "dbus-objects/TimeoutObject.h"
#include "common/Exceptions.h"

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
    virtual void setBuilderParams(std::shared_ptr<BaseReader> reader) = 0;

    virtual void build() = 0;
    virtual std::map<VariantKey, VariantValue> getBuiltConfig() = 0;
protected:
    std::shared_ptr<BaseReader> m_reader{};
    std::map<VariantKey, VariantValue> m_builtConfig{};
};

class DbusObjectBuilder : public BaseDbusObjectBuilder {
public:
    DbusObjectBuilder() = default;
    void setBuilderParams(std::shared_ptr<BaseReader> reader) override;
    void build() override;

    std::map<VariantKey, VariantValue> getBuiltConfig() override;

};





#endif