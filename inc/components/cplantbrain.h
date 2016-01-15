#ifndef CPLANTBRAIN_H
#define CPLANTBRAIN_H

#include "common.h"
#include "component.h"

struct CPlantBrain : public Component
{
    virtual bool init(YAML::Node node);
};

inline std::shared_ptr<Component> createCPlantBrain()
{
    return std::make_shared<CPlantBrain>();
}

#endif // CPLANTBRAIN_H
