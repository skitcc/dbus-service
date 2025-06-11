#include "ProxiesBuilder.h"
#include "boost/json.hpp"
#include <fstream>
#include "common/Config.h"
#include "common/Exceptions.h"


ProxiesBuilder::ProxiesBuilder() {
    m_reader = std::make_shared<PathTypeJsonReader>(dbus_daemon::Config::getClientConfigPath());
}


bool ProxiesBuilder::build() {
    try {
        while (auto object = m_reader->nextObject()) {
            m_proxiesConfigurations.push_back(object.value());
        }
        return true;
    } catch(...) {
        return false;
    }
}


const std::vector<ClientConfiguration>& ProxiesBuilder::getProxiesConfigurations() {
    return m_proxiesConfigurations;
}


