#ifndef CSPAWN_H
#define CSPAWN_H

#include "common.h"
#include "component.h"
#include "vec2.h"

struct CSpawn : public Component
{
    bool active;

    int energyCost;
    int energyRequired;
    Vec2 pos;
    EntityType type;

    virtual bool init(YAML::Node node);
};

inline std::shared_ptr<Component> createCSpawn()
{
    return std::make_shared<CSpawn>();
}

#endif // CSPAWN_H
