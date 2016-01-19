#ifndef CSPAWN_H
#define CSPAWN_H

#include "common.h"
#include "component.h"
#include "vec2.h"

struct CSpawn : public Component
{
    INC_FACTORY_REGISTER(CSpawn);
 
    bool active;

    int energyCost;
    int energyRequired;
    Vec2 pos;
    EntityType type;

    virtual bool init(YAML::Node node);
};

#endif // CSPAWN_H
