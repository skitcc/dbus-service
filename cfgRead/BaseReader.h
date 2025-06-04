#ifndef BASE_READER_H
#define BASE_READER_H

#include <optional>
#include <variant>
#include <string>
#include <map>
#include <string_view>
#include <fstream>
#include <queue>

enum class cfgType : size_t{
    TIMEOUT = 0,
};

class BaseReader {
public:
    virtual ~BaseReader() = default;
protected:
    using VariantKey = std::optional<std::string>;
    using VariantValue = std::optional<std::variant<int, std::string>>;

    using Field = std::pair<VariantKey, VariantValue>;

    virtual Field nextField() = 0;

    const std::map<std::string, cfgType> m_relations{
        {"Timeout", cfgType::TIMEOUT},
    };
};




#endif