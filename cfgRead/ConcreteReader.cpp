#include "ConcreteReader.h"
#include "exceptions/Exceptions.h"
#include <iostream>

namespace {
    constexpr std::string_view META_HEADER = "--META--";
    constexpr std::string_view META_FOOTER = "--------";
}

ConcreteReader::ConcreteReader(const std::string_view& filename) {
    m_stream.open(filename.data());
    if (!m_stream.is_open()) {
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    }
}

void ConcreteReader::setFile(const std::filesystem::path& path) {
    if (m_stream.is_open())
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);

    m_stream.open(path);

    if (!m_stream.is_open())
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    
}

std::istream& operator>>(std::istream& stream, typename ConcreteReader::VariantValue& value) {
    std::string typeTag;
    if (!std::getline(stream, typeTag, ':')) {
        throw NoTypeTagException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    }

    if (typeTag == "int") {
        int val;
        if (!(stream >> val)) {
            throw InvalidValueException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
        }
        value = val;
    } else if (typeTag == "string") {
        std::string val;
        if (!(stream >> val)) {
            throw InvalidValueException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
        }
        value = val;
    } else {
        throw UnsupportedTypeTag(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    }
    return stream;
}



typename ConcreteReader::Field ConcreteReader::nextField() {
    if (m_fieldQueue.empty() && !m_stream.eof()) 
    lineIterator();
    if (m_fieldQueue.empty())
        return std::nullopt;

    auto field = m_fieldQueue.front();
    m_fieldQueue.pop();
    return field;
}

cfgType ConcreteReader::readMeta() {
    m_stream.seekg(0);
    std::string metaBuffer{};

    if (!std::getline(m_stream, metaBuffer)) {
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    }

    if (metaBuffer != META_HEADER)
        throw MetaSectionError(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);

    if (!std::getline(m_stream, metaBuffer)) {
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    }

    auto it = m_relations.find(metaBuffer);
    if (it == m_relations.end()) {
        throw UnsupportedConfiguration(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    }

    if (!std::getline(m_stream, metaBuffer)) {
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    }

    if (metaBuffer != META_FOOTER)
        throw MetaSectionError(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);

    std::cout << "meta readed! " << "type " <<  int(it->second) << '\n';

    return it->second;
}

void ConcreteReader::readField(std::stringstream& stream) {
    std::string key{};
    VariantValue value;

    if (!(stream >> key >> value)) {
        throw InvalidValueException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    }

    m_fieldQueue.push(std::make_pair(key, value));
}


void ConcreteReader::lineIterator() {
    std::string buffer{};
    std::stringstream ss{};


    if (!std::getline(m_stream, buffer)) {
        if (m_stream.eof())
            return;
        throw FileException(__FILE__, typeid(ConcreteReader).name(), __FUNCTION__);
    }

    ss.str(std::move(buffer));
    readField(ss);
    
}

