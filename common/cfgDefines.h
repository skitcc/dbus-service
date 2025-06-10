#ifndef CFG_DEFINES_H
#define CFG_DEFINES_H

#include <stddef.h>
#include <vector>
#include <map>
#include <tuple>
#include <sdbus-c++/Types.h>

enum class cfgType : size_t{
    TIMEOUT = 0,
};


using VariantKey = std::string;
using VariantValue = std::variant<int, std::string>;

using Field = std::pair<VariantKey, VariantValue>;

using FileConfiguration = std::map<VariantKey, VariantValue>;

using DbusObjectsConfigurations = std::vector<std::tuple<sdbus::ObjectPath, cfgType, std::map<VariantKey, VariantValue>>>;



#endif