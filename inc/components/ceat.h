#ifndef CEAT_H
#define CEAT_H

#include "common.h"
#include "component.h"

class CEat : public Component
{
    INC_FACTORY_REGISTER(CEat);

public:
    bool active;

    Dir dir;
    std::vector<EntityType> food;
    std::map<EntityType, int> energyFromFood;

    virtual bool init(YAML::Node node);
};

#endif // CEAT_H
