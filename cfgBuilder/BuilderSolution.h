#ifndef BUILDER_SOLUTION_H
#define BUILDER_SOLUTION_H

#include "BaseBuilder.h"

class BuilderSolution {

public:
    static std::shared_ptr<BaseConfigBuilder> create(std::string_view filename);

    
};


#endif