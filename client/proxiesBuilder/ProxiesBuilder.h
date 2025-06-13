#ifndef PROXIES_BUILDER_H
#define PROXIES_BUILDER_H

#include <vector>
#include <sdbus-c++/Types.h>
#include "common/cfgDefines.h"
#include "proxyReader/PathTypeJsonReader.h"


class ProxiesBuilder {
public:
    ProxiesBuilder();
    bool build();
    const std::vector<ClientConfiguration>& getProxiesConfigurations();

private:
    std::vector<ClientConfiguration> m_proxiesConfigurations;

    std::shared_ptr<BaseProxyReader> m_reader;

    const std::map<std::string, cfgType> m_relations {
        {"Timeout", cfgType::TIMEOUT},
    };
};
 



#endif
