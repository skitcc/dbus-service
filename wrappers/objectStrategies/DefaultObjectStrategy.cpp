#include "DefaultObjectStrategy.h"
#include "exceptions/Exceptions.h"

void DefaultObjectStrategy::changeConfiguration(const std::string& key, const Variant& value) {

    auto it = m_conf.find(key);
    if (it == m_conf.end()) {
        throw UnsupportedKeyConfiguration(__FILE__, typeid(DefaultObjectStrategy).name(), __FUNCTION__);
    }

    m_conf[key] = value;
}


std::map<std::string, typename DefaultObjectStrategy::Variant> DefaultObjectStrategy::getConfiguration() {
    return m_conf;
}