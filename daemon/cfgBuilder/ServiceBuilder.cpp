#include "ServiceBuilder.h"
#include <sdbus-c++/Types.h>
#include "common/Config.h"
#include <iostream>


ServiceBuilder::ServiceBuilder() {
    m_reader = std::make_shared<ConcreteReader>();
    initConnection();
}

bool ServiceBuilder::build() {
    collectAllConfigs();
    std::shared_ptr<BaseDbusObjectBuilder> configBuilder = std::make_shared<DbusObjectBuilder>();
    
    bool builtCorrect = true;

    try {
        for (const auto& path : m_configPaths) {
            std::string filename = path.filename().string();
            std::replace(filename.begin(), filename.end(), '.', '_');
            if (filename.find_last_of('.') != std::string::npos) {
                filename = filename.substr(0, filename.find_last_of('.'));
            }
            sdbus::ObjectPath currentPath = sdbus::ObjectPath{dbus_daemon::Config::getBaseObjectPath() + "/" + filename};
            std::cout << "Processing path: " << currentPath << "\n";
            m_reader->setFile(path);
            auto confType = m_reader->readMeta();
            
            configBuilder->setBuilderParams(m_reader, confType);
            configBuilder->setObjectAttributes(*m_connection, currentPath);
            configBuilder->build();
        }

    } catch(...) {
        builtCorrect = false;
    }
    return builtCorrect;
}


sdbus::IConnection& ServiceBuilder::getConnection() {
    return *m_connection;
}


void ServiceBuilder::collectAllConfigs() {
    for (const auto& entry : std::filesystem::directory_iterator(dbus_daemon::Config::getConfigurationDir())) {
        if (entry.is_regular_file()) {
            std::cout << entry.path() << '\n';
            m_configPaths.push_back(entry.path());
        }
    }
}

void ServiceBuilder::initConnection() {
    m_connection = sdbus::createSessionBusConnection();
    sdbus::ServiceName serviceName = dbus_daemon::Config::getServiceName(); 
    try {
        m_connection->requestName(serviceName);
        std::cout << "Service name acquired: com.system.configurationManager\n";
    } catch (const sdbus::Error& e) {
        std::cout << "Failed to acquire service name: " << e.getName() << " - " << e.getMessage() << "\n";
        throw e;
    }
}