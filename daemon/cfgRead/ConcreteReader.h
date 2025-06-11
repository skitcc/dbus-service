#ifndef CONCRETE_READER_H
#define CONCRETE_READER_H

#include "BaseReader.h"
#include <optional>
#include <string>
#include <sstream>
#include <string_view>
#include <fstream>
#include <queue>


class ConcreteReader final: public BaseReader {
public:
    ConcreteReader() = default;
    ConcreteReader(const std::string_view& filename);
    std::optional<Field> nextField() override;
    void setFile(const std::filesystem::path& path) override;
    std::string readMeta() override;

private:
    std::ifstream m_stream;

    std::queue<Field> m_fieldQueue;

    void readField(std::stringstream& stream);

    void lineIterator();

    friend std::istream& operator>>(std::istream& stream, VariantValue& val);
};



#endif
    