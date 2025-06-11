#ifndef PATH_TYPE_JSON_READER_H
#define PATH_TYPE_JSON_READER_H

#include "BaseProxyReader.h"


class PathTypeJsonReader : public JsonReader {
public:
    explicit PathTypeJsonReader(const std::filesystem::path& path);

    std::optional<ClientConfiguration> nextObject() override;
    void setFile(const std::filesystem::path& path) override;


protected:
    void parseJson(const std::filesystem::path& path) override;

};



#endif