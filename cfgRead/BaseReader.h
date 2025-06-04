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
    using Variant = std::optional<std::variant<int, std::string>>;

    virtual std::pair<std::string, Variant> nextField() = 0;

    const std::map<std::string, cfgType> m_relations{
        {"Timeout", cfgType::TIMEOUT},
    };
};




#endif