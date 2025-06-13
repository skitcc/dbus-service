#ifndef COMPOSITE_BUILDER_H
#define COMPOSITE_BUILDER_H

#include "DbusObjectBuilder.h"
#include "boost/json.hpp"
#include "cfgRead/ConcreteReader.h"
#include "dbus-objects/BaseDbusObject.h"
#include <filesystem>
#include <sdbus-c++/IConnection.h>

class ServiceBuilder
{
public:
    ServiceBuilder();
    bool build();

    std::vector<std::shared_ptr<BaseDbusObject>> getConfiguratedObjects();

private:
    bool collectAllConfigs();

    std::vector<std::filesystem::path> m_configPaths;
    std::shared_ptr<BaseReader> m_reader;
    std::vector<std::shared_ptr<BaseDbusObject>> m_configuratedObjects;
    std::map<std::string, cfgType> m_relations;
};

void pretty_print(std::ostream &os,
                  const boost::json::value &jv,
                  int indent = 0,
                  int indent_size = 4);

#endif