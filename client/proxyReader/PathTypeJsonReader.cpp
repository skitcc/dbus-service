#include "PathTypeJsonReader.h"
#include "common/Exceptions.h"

PathTypeJsonReader::PathTypeJsonReader(const std::filesystem::path &path)
{
    m_stream.close();
    m_array = boost::json::array{};
    m_currentIndex = 0;
    parseJson(path);
}

void PathTypeJsonReader::setFile(const std::filesystem::path &path)
{
    m_stream.close();
    m_array = boost::json::array{};
    m_currentIndex = 0;
    parseJson(path);
}

void PathTypeJsonReader::parseJson(const std::filesystem::path &path)
{
    m_stream.open(path);
    if (!m_stream.is_open()) {
        throw FileException(__FILE__, typeid(PathTypeJsonReader).name(), __FUNCTION__, __LINE__);
    }

    std::stringstream buffer;
    buffer << m_stream.rdbuf();
    std::string content = buffer.str();
    m_stream.close();

    boost::json::error_code ec;
    boost::json::value jv = boost::json::parse(content, ec);
    if (ec) {
        throw FileException(__FILE__, typeid(PathTypeJsonReader).name(), __FUNCTION__, __LINE__);
    }

    if (!jv.is_array()) {
        throw FileException(__FILE__, typeid(PathTypeJsonReader).name(), __FUNCTION__, __LINE__);
    }

    m_array = jv.as_array();
}

std::optional<ClientConfiguration> PathTypeJsonReader::nextObject()
{
    if (m_currentIndex >= m_array.size()) {
        return std::nullopt;
    }

    boost::json::value &value = m_array[m_currentIndex];
    ++m_currentIndex;

    if (!value.is_object()) {
        return std::nullopt;
    }

    boost::json::object &object = value.as_object();

    if (!object.contains("ObjectPath") || !object.at("ObjectPath").is_string()) {
        return std::nullopt;
    }
    if (!object.contains("ObjectType") || !object.at("ObjectType").is_string()) {
        return std::nullopt;
    }

    std::string path_str = std::string(object.at("ObjectPath").as_string());
    std::string type_str = std::string(object.at("ObjectType").as_string());

    auto it = m_relations.find(type_str);
    if (it == m_relations.end()) {
        throw UnsupportedConfiguration(__FILE__, typeid(PathTypeJsonReader).name(), __FUNCTION__);
    }

    try {
        sdbus::ObjectPath path(path_str);
        return ClientConfiguration{path, it->second};
    }
    catch (const std::exception &e) {
        return std::nullopt;
    }
}