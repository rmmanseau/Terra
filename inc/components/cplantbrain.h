#ifndef CPLANTBRAIN_H
#define CPLANTBRAIN_H

#include "common.h"
#include "component.h"

class CPlantBrain : public Component
{
    INC_FACTORY_REGISTER(CPlantBrain);

public: 
    virtual bool init(YAML::Node node);
};

#endif // CPLANTBRAIN_H
