#ifndef CONCRETE_READER_H
#define CONCRETE_READER_H

#include "BaseReader.h"
#include <string>
#include <sstream>


class ConcreteReader final: public BaseReader {
public:
    ConcreteReader(std::string_view filename);
    ~ConcreteReader();

    std::pair<std::string, Variant> nextField() override;

private:
    std::ifstream m_stream;

    cfgType readMeta();
    std::queue<std::pair<std::string, Variant>> m_fieldQueue;

    void readField(std::stringstream& stream);

    void lineIterator();

    friend std::istream& operator>>(std::istream& stream, Variant& val);

};



#endif
    