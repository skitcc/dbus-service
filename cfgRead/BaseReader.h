#ifndef BASE_READER_H
#define BASE_READER_H

#include <optional>
#include <variant>
#include <string>
#include <map>
#include <filesystem>

enum class cfgType : size_t{
    TIMEOUT = 0,
};

class BaseReader {
protected:
    using VariantKey = std::string;
    using VariantValue = std::variant<int, std::string>;
    using Field = std::optional<std::pair<VariantKey, VariantValue>>;

public:
    virtual ~BaseReader() = default;
    virtual Field nextField() = 0;
    virtual void setFile(const std::filesystem::path& path) = 0;
    virtual cfgType readMeta() = 0;

protected:
    const std::map<std::string, cfgType> m_relations {
        {"Timeout", cfgType::TIMEOUT},
    };

};




#endif