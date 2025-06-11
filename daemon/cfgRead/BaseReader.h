#ifndef BASE_READER_H
#define BASE_READER_H

#include <variant>
#include <string>
#include <filesystem>
#include "common/cfgDefines.h"


class BaseReader {
public:
    virtual ~BaseReader() = default;
    virtual std::optional<Field> nextField() = 0;
    virtual void setFile(const std::filesystem::path& path) = 0;
    virtual std::string readMeta() = 0;

protected:
    const std::map<std::string, cfgType> m_relations {
        {"Timeout", cfgType::TIMEOUT},
    };

};




#endif