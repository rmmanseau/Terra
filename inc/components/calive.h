#ifndef CALIVE_H
#define CALIVE_H

#include "common.h"
#include "component.h"

class CAlive : public Component
{
    INC_FACTORY_REGISTER(CAlive);

public:
    int energy;
    int energyMax;
    int health;
    int healthMax;

    virtual bool init(YAML::Node node);

    void updateEnergy(int amount);
    void updateHealth(int amount);
    void kill();
};

#endif // CALIVE_H
