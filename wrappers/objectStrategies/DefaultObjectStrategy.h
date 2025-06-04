#ifndef TIMEOUT_METHOD_IMPL_H
#define TIMEOUT_METHOD_IMPL_H


#include "BaseObjectStrategy.h"

class DefaultObjectStrategy : public BaseObjectStrategy {
public:
    DefaultObjectStrategy(std::map<std::string, Variant> conf) 
        : BaseObjectStrategy(conf) {}

    
    void changeConfiguration(const std::string& key, const Variant& value);
    std::map<std::string, Variant> getConfiguration();

};



#endif