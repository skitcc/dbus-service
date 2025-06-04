#ifndef BASE_BUILDER_H
#define BASE_BUILDER_H

#include "cfgRead/BaseReader.h"
#include "wrappers/BaseDbusObject.h"
#include <memory>


class BaseConfigBuilder {
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
    ConcreteConfigBuilder(std::shared_ptr<BaseReader> reader, std::shared_ptr<BaseDbusObject> object) : BaseConfigBuilder(reader, object) {}

    bool build() override;


};





#endif