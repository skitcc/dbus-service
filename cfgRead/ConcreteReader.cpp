#include "ConcreteReader.h"
#include <exception>

namespace {
    constexpr std::string_view META_HEADER = "--META--";
    constexpr std::string_view META_FOOTER = "--------";
}

std::istream& operator>>(std::istream& stream, typename ConcreteReader::Variant& value) {
    std::string typeTag;
    if (!std::getline(stream, typeTag, ':')) {
        throw std::runtime_error("Type tag not found!");
    }

    if (typeTag == "int") {
        int val;
        if (!(stream >> val)) {
            throw std::runtime_error("Value not found!");
        }
        value = val;
    } else if (typeTag == "string") {
        std::string val;
        if (!(stream >> val)) {
            throw std::runtime_error("Value not found!");
        }
        value = val;
    } else {
        throw std::runtime_error("Unsupported type tag!");
    }
    return stream;
}


ConcreteReader::ConcreteReader(std::string_view filename) {
    m_stream.open(filename.data());
    if (!m_stream.is_open()) {
        throw std::runtime_error("Error while open file!");
    }
}

std::pair<std::string, typename ConcreteReader::Variant> ConcreteReader::nextField() {
    if (m_fieldQueue.empty() && !m_stream.eof()) 
    lineIterator();
    if (m_fieldQueue.empty())
        return std::make_pair(std::string{}, std::nullopt);

    auto field = m_fieldQueue.front();
    m_fieldQueue.pop();
    return field;
}

cfgType ConcreteReader::readMeta() {
    m_stream.seekg(0);
    std::string metaBuffer{};

    if (!std::getline(m_stream, metaBuffer)) {
        throw std::runtime_error("Error reading");
    }

    if (metaBuffer != META_HEADER)
        throw std::runtime_error("Error in meta section!");

    if (!std::getline(m_stream, metaBuffer)) {
        throw std::runtime_error("Error reading");
    }

    auto it = m_relations.find(metaBuffer);
    if (it == m_relations.end()) {
        throw std::runtime_error("Unsupported cfg");
    }

    if (!std::getline(m_stream, metaBuffer)) {
        throw std::runtime_error("Error reading");
    }

    if (metaBuffer != META_FOOTER)
        throw std::runtime_error("Error in meta section!");

    return it->second;
}

void ConcreteReader::readField(std::stringstream& stream) {
    std::string key{};
    Variant value;

    if (!(stream >> key >> value)) {
        throw std::runtime_error("Data error!");
    }

    m_fieldQueue.push(std::make_pair(key, value));
}


void ConcreteReader::lineIterator() {
    std::string buffer{};
    std::stringstream ss{};


    if (!std::getline(m_stream, buffer)) {
        if (m_stream.eof())
            return;
        throw std::runtime_error("Error in field read");
    }

    ss.str(std::move(buffer));
    readField(ss);
    
}


ConcreteReader::~ConcreteReader() {
    if (m_stream.is_open())
        m_stream.close();
}