#ifndef COMPOSITE_BUILDER_H
#define COMPOSITE_BUILDER_H


#include <filesystem>
#include "cfgRead/ConcreteReader.h"
#include "DbusObjectBuilder.h"
#include <sdbus-c++/IConnection.h>


class ServiceBuilder {
public:
    ServiceBuilder();
    bool build();
    
    sdbus::IConnection& getConnection();

private:

    void collectAllConfigs();
    void initConnection();


    std::vector<std::filesystem::path> m_configPaths;
    std::shared_ptr<BaseReader> m_reader;
    std::unique_ptr<sdbus::IConnection> m_connection;


};




#endif