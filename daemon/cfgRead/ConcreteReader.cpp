#include "ConcreteReader.h"
#include "common/Exceptions.h"
#include <algorithm>
#include <iostream>

namespace {
constexpr std::string_view META_HEADER = "--META--";
constexpr std::string_view META_FOOTER = "--------";
}

ConcreteReader::ConcreteReader(const std::string_view &filename)
{
    m_stream.open(filename.data());
    if (!m_stream.is_open()) {
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }
}

void ConcreteReader::setFile(const std::filesystem::path &path)
{
    m_stream.close();

    m_stream.open(path);

    if (!m_stream.is_open()) {
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }
}

std::istream &operator>>(std::istream &stream, VariantValue &value)
{
    std::string typeTag;
    if (!std::getline(stream, typeTag, ':')) {
        throw NoTypeTagException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }

    typeTag.erase(std::remove_if(typeTag.begin(),
                                 typeTag.end(),
                                 [](unsigned char c) { return std::isspace(c); }),
                  typeTag.end());

    if (typeTag == "int") {
        int val;
        if (!(stream >> val)) {
            throw InvalidValueException(__FILE__,
                                        typeid(ConcreteReader).name(),
                                        __FUNCTION__,
                                        __LINE__);
        }
        value = val;
    } else if (typeTag == "string") {
        std::string val;
        if (!(stream >> val)) {
            throw InvalidValueException(__FILE__,
                                        typeid(ConcreteReader).name(),
                                        __FUNCTION__,
                                        __LINE__);
        }
        value = val;
    } else {
        throw UnsupportedTypeTag(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }
    return stream;
}

std::optional<Field> ConcreteReader::nextField()
{
    if (m_fieldQueue.empty() && !m_stream.eof()) {
        lineIterator();
    }
    if (m_fieldQueue.empty()) {
        return std::nullopt;
    }

    auto field = m_fieldQueue.front();
    m_fieldQueue.pop();
    return field;
}

std::string ConcreteReader::readMeta()
{
    m_stream.seekg(0);
    std::string metaBuffer{};

    if (!std::getline(m_stream, metaBuffer)) {
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }

    if (metaBuffer != META_HEADER) {
        throw MetaSectionError(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }

    if (!std::getline(m_stream, metaBuffer)) {
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }

    auto it = m_relations.find(metaBuffer);
    if (it == m_relations.end()) {
        throw UnsupportedConfiguration(__FILE__,
                                       typeid(ConcreteReader).name(),
                                       __FUNCTION__,
                                       __LINE__);
    }
    std::string result = metaBuffer;
    if (!std::getline(m_stream, metaBuffer)) {
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }

    if (metaBuffer != META_FOOTER) {
        throw MetaSectionError(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }

    return result;
}

void ConcreteReader::readField(std::stringstream &stream)
{
    std::string key{};
    VariantValue value;
    if (!(stream >> key >> value)) {
        throw InvalidValueException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }

    m_fieldQueue.push(std::make_pair(key, value));
}

void ConcreteReader::lineIterator()
{
    std::string buffer{};
    std::stringstream ss{};

    if (!std::getline(m_stream, buffer)) {
        if (m_stream.eof()) {
            return;
        }
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__, __LINE__);
    }

    ss.str(std::move(buffer));
    readField(ss);
}
