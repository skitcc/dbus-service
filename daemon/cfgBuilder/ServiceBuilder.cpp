#include "ServiceBuilder.h"
#include <sdbus-c++/Types.h>
#include "common/Config.h"
#include "common/ObjectInfoStorage.h"
#include <iostream>


ServiceBuilder::ServiceBuilder() {
    m_reader = std::make_shared<ConcreteReader>();
}

bool ServiceBuilder::build() {
    collectAllConfigs();
    std::shared_ptr<BaseDbusObjectBuilder> configBuilder = std::make_shared<DbusObjectBuilder>();
    
    bool builtCorrect = true;
    auto objectStorage = ObjectInfoStorage::instance();

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

            auto cfgType = m_reader->readMeta();
            configBuilder->setBuilderParams(m_reader);
            
            auto config = configBuilder->getBuiltConfig();
            objectStorage->addDbusConfiguration(currentPath, cfgType, config);
        }

    } catch(...) {
        builtCorrect = false;
    }
    return builtCorrect;
}


std::vector<std::shared_ptr<BaseDbusObject>> ServiceBuilder::getConfiguratedObjects() {
    return m_configuratedObjects;
}

void ServiceBuilder::collectAllConfigs() {
    for (const auto& entry : std::filesystem::directory_iterator(dbus_daemon::Config::getConfigurationDir())) {
        if (entry.is_regular_file()) {
            std::cout << entry.path() << '\n';
            m_configPaths.push_back(entry.path());
        }
    }
}
