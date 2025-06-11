#include "ServiceBuilder.h"
#include <sdbus-c++/Types.h>
#include "common/Config.h"
#include "common/ObjectInfoStorage.h"
#include <iostream>


ServiceBuilder::ServiceBuilder() {
    m_reader = std::make_shared<ConcreteReader>();
    m_relations = {
        {"Timeout", cfgType::TIMEOUT},
    };
}

bool ServiceBuilder::build() {
    bool builtCorrect = true;

    if (!collectAllConfigs()) {
        builtCorrect = false;
        std::cout << "No such directory for configs!\n";
    }

    std::shared_ptr<BaseDbusObjectBuilder> configBuilder = std::make_shared<DbusObjectBuilder>();
    
    auto objectStorage = ObjectInfoStorage::instance();

    boost::json::array arrayForClient;
    std::ofstream clientFile(dbus_daemon::Config::getClientConfigPath());

    try {
        for (const auto& path : m_configPaths) {
            std::string filename = path.filename().string();
            std::replace(filename.begin(), filename.end(), '.', '_');
            if (filename.find_last_of('.') != std::string::npos) {
                filename = filename.substr(0, filename.find_last_of('.'));
            }
            sdbus::ObjectPath currentPath = sdbus::ObjectPath{dbus_daemon::Config::getBaseObjectPath() + "/" + filename};
            
            m_reader->setFile(path);

            auto cfgType = m_reader->readMeta();
            boost::json::object object;
            object["ObjectPath"] = std::string(currentPath);
            object["ObjectType"] = std::string(cfgType);

            std::cout << "Adding object: " << boost::json::serialize(object) << std::endl;
            arrayForClient.push_back(object);

            configBuilder->setBuilderParams(m_reader);
            
            auto config = configBuilder->getBuiltConfig();
            objectStorage->addDbusConfiguration(currentPath, config);
        }
        pretty_print(clientFile, arrayForClient);
    } catch(...) {
        builtCorrect = false;
    }
    return builtCorrect;
}


std::vector<std::shared_ptr<BaseDbusObject>> ServiceBuilder::getConfiguratedObjects() {
    return m_configuratedObjects;
}

bool ServiceBuilder::collectAllConfigs() {
    if (!std::filesystem::is_directory(dbus_daemon::Config::getConfigurationDir()))
        return false;

    for (const auto& entry : std::filesystem::directory_iterator(dbus_daemon::Config::getConfigurationDir())) {
        if (entry.is_regular_file()) {
            m_configPaths.push_back(entry.path());
        }
    }
    return true;
}

void pretty_print(std::ostream& os, const boost::json::value& jv, int indent, int indent_size) {
    using namespace boost::json;

    auto write_indent = [&os](int level, int size) {
        os << std::string(level * size, ' ');
    };

    if (jv.is_null()) {
        os << "null";
    } else if (jv.is_bool()) {
        os << (jv.as_bool() ? "true" : "false");
    } else if (jv.is_number()) {
        os << jv;
    } else if (jv.is_string()) {
        std::string str = std::string(jv.as_string());
        os << "\"" << str << "\""; 
    } else if (jv.is_array()) {
        const array& arr = jv.as_array();
        if (arr.empty()) {
            os << "[]";
            return;
        }
        os << "[\n";
        for (size_t i = 0; i < arr.size(); ++i) {
            write_indent(indent + 1, indent_size);
            pretty_print(os, arr[i], indent + 1, indent_size);
            if (i < arr.size() - 1) {
                os << ",";
            }
            os << "\n";
        }
        write_indent(indent, indent_size);
        os << "]";
    } else if (jv.is_object()) {
        const object& obj = jv.as_object();
        if (obj.empty()) {
            os << "{}";
            return;
        }
        os << "{\n";
        size_t i = 0;
        for (const auto& [key, value] : obj) {
            write_indent(indent + 1, indent_size);
            os << "\"" << key << "\": ";
            pretty_print(os, value, indent + 1, indent_size);
            if (i++ < obj.size() - 1) {
                os << ",";
            }
            os << "\n";
        }
        write_indent(indent, indent_size);
        os << "}";
    }
}