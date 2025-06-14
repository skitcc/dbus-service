#ifndef CFG_DEFINES_H
#define CFG_DEFINES_H

#include <map>
#include <sdbus-c++/Types.h>
#include <stddef.h>
#include <tuple>
#include <vector>

enum class cfgType : size_t {
    TIMEOUT = 0,
};

using VariantKey = std::string;
using VariantValue = std::variant<int, std::string>;

using Field = std::pair<VariantKey, VariantValue>;

using FileConfiguration = std::map<VariantKey, VariantValue>;

using DbusObjectsConfigurations
    = std::vector<std::tuple<sdbus::ObjectPath, std::map<VariantKey, VariantValue>, std::string>>;

using ClientConfiguration = std::pair<sdbus::ObjectPath, cfgType>;

#endif