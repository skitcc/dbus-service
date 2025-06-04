#ifndef BASE_METHOD_IMPL_H
#define BASE_METHOD_IMPL_H

#include <map>
#include <optional>
#include <variant>
#include <string>


class BaseObjectStrategy {
protected:
    using Variant = std::optional<std::variant<int, std::string>>;

public:
    BaseObjectStrategy(std::map<std::string, Variant> conf) 
    : m_conf(conf) {}

    virtual ~BaseObjectStrategy() = default;

protected:
    std::map<std::string, Variant> m_conf;

};







#endif