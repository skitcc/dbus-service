#ifndef CONCRETE_READER_H
#define CONCRETE_READER_H

#include "BaseReader.h"
#include <string>
#include <sstream>


class ConcreteReader final: public BaseReader {
public:
    ConcreteReader(const std::string_view& filename);
    Field nextField() override;

private:
    std::ifstream m_stream;

    cfgType readMeta();
    std::queue<Field> m_fieldQueue;

    void readField(std::stringstream& stream);

    void lineIterator();

    friend std::istream& operator>>(std::istream& stream, VariantValue& val);
};



#endif
    