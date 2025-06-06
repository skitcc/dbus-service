#include "ServiceBuilder.h"
#include <sdbus-c++/Types.h>
#include <sdbus-c++/IConnection.h>
#include <iostream>


ServiceBuilder::ServiceBuilder() {
    m_reader = std::make_shared<ConcreteReader>();
    m_service = std::make_shared<Service>();
}

bool ServiceBuilder::build() {
    collectAllConfigs();
    std::shared_ptr<BaseDbusObjectBuilder> configBuilder = std::make_shared<DbusObjectBuilder>();

    std::string objectPath{"/com/system/configurationManager/Application"};
    
    bool builtCorrect = true;

    try {
        for (const auto& path : m_configPaths) {
            std::string filename = path.filename().string();
            std::replace(filename.begin(), filename.end(), '.', '_');
            if (filename.find_last_of('.') != std::string::npos) {
                filename = filename.substr(0, filename.find_last_of('.'));
            }
            sdbus::ObjectPath currentPath = sdbus::ObjectPath{objectPath + "/" + filename};
            std::cout << "Processing path: " << currentPath << "\n";
            m_reader->setFile(path);
            auto confType = m_reader->readMeta();
            
            configBuilder->setBuilderParams(m_reader, confType);
            configBuilder->setObjectAttributes(m_service->getConnection(), currentPath);
            auto object = configBuilder->getBuildedObject();
            m_service->addObject(object);        
        }
    } catch(...) {
        builtCorrect = false;
    }
    return builtCorrect;
}

std::shared_ptr<Service> ServiceBuilder::getService() {
    return m_service;
}


void ServiceBuilder::collectAllConfigs() {
    for (const auto& entry : std::filesystem::directory_iterator(CONFIG_DIR)) {
        if (entry.is_regular_file()) {
            std::cout << entry.path() << '\n';
            m_configPaths.push_back(entry.path());
        }
    }
}