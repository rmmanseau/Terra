#ifndef CEGGBRAIN_H
#define CEGGBRAIN_H

#include "common.h"
#include "component.h"

class CEggBrain : public Component
{
    INC_FACTORY_REGISTER(CEggBrain);

public: 
    virtual bool init(YAML::Node node);
};

#endif // CEGGBRAIN_H
