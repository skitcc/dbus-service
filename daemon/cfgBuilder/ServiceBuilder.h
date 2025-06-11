#ifndef COMPOSITE_BUILDER_H
#define COMPOSITE_BUILDER_H


#include <filesystem>
#include "cfgRead/ConcreteReader.h"
#include "DbusObjectBuilder.h"
#include "dbus-objects/BaseDbusObject.h"
#include <sdbus-c++/IConnection.h>
#include "boost/json.hpp"



class ServiceBuilder {
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

void pretty_print(std::ostream& os, const boost::json::value& jv, int indent = 0, int indent_size = 4);


#endif