#ifndef BASE_BUILDER_H
#define BASE_BUILDER_H

#include "cfgRead/BaseReader.h"
#include "cfgRead/ConcreteReader.h"
#include "wrappers/BaseDbusObject.h"
#include <memory>


class BaseConfigBuilder {
protected:
    using VariantKey = std::optional<std::string>;
    using VariantValue = std::optional<std::variant<int, std::string>>;

    using Field = std::pair<VariantKey, VariantValue>;

public:
    BaseConfigBuilder(std::shared_ptr<BaseReader> reader, std::shared_ptr<BaseDbusObject> object) : m_reader(reader), m_object(object) {}

    virtual ~BaseConfigBuilder() = default;
    virtual bool build() = 0;

protected:
    std::shared_ptr<BaseReader> m_reader;
    std::shared_ptr<BaseDbusObject> m_object;


};

class ConcreteConfigBuilder : public BaseConfigBuilder {
public:
    ConcreteConfigBuilder(std::shared_ptr<BaseReader> reader, std::shared_ptr<BaseDbusObject> object) 
        : BaseConfigBuilder(std::make_shared<ConcreteReader>(), object) {}

    bool build() override;


};





#endif