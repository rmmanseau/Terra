#ifndef CSPAWN_H
#define CSPAWN_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CSpawn : public Component
{
    INC_FACTORY_REGISTER(CSpawn);
    
public:
    bool active;

    int energyCost;
    int energyRequired;
    Vec2i pos;
    EntityType type;

    virtual bool init(YAML::Node node);
};

#endif // CSPAWN_H
