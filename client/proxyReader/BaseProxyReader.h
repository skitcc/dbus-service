#ifndef PROXY_READER_H
#define PROXY_READER_H

#include "boost/json.hpp"
#include "common/cfgDefines.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <variant>

class BaseProxyReader
{
public:
    virtual std::optional<ClientConfiguration> nextObject() = 0;
    virtual void setFile(const std::filesystem::path &path) = 0;

    virtual ~BaseProxyReader() = default;

protected:
    std::ifstream m_stream;
    boost::json::array m_array;
    size_t m_currentIndex{0};
    const std::map<std::string, cfgType> m_relations{
        {"Timeout", cfgType::TIMEOUT},
    };
};

class JsonReader: public BaseProxyReader
{
public:
    virtual std::optional<ClientConfiguration> nextObject() = 0;
    virtual void setFile(const std::filesystem::path &path) = 0;

    virtual ~JsonReader() = default;

protected:
    virtual void parseJson(const std::filesystem::path &path) = 0;
};

#endif