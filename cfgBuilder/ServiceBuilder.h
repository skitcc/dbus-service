#ifndef COMPOSITE_BUILDER_H
#define COMPOSITE_BUILDER_H


#include <filesystem>
#include "service/Service.h"
#include "cfgRead/ConcreteReader.h"
#include "DbusObjectBuilder.h"


class ServiceBuilder {
public:
    ServiceBuilder();
    bool build();
    std::shared_ptr<Service> getService();

private:

    void collectAllConfigs();

    std::shared_ptr<Service> m_service;
    std::vector<std::filesystem::path> m_configPaths;
    std::shared_ptr<BaseReader> m_reader;

    static constexpr std::string_view CONFIG_DIR = "../data/";

};




#endif