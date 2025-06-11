#ifndef COMPOSITE_BUILDER_H
#define COMPOSITE_BUILDER_H


#include <filesystem>
#include "cfgRead/ConcreteReader.h"
#include "DbusObjectBuilder.h"
#include "dbus-objects/BaseDbusObject.h"
#include <sdbus-c++/IConnection.h>


class ServiceBuilder {
public:
    ServiceBuilder();
    bool build();

    std::vector<std::shared_ptr<BaseDbusObject>> getConfiguratedObjects();
    

private:

    void collectAllConfigs();

    std::vector<std::filesystem::path> m_configPaths;
    std::shared_ptr<BaseReader> m_reader;
    std::vector<std::shared_ptr<BaseDbusObject>> m_configuratedObjects;


};




#endif