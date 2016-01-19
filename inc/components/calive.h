#ifndef CALIVE_H
#define CALIVE_H

#include "common.h"
#include "component.h"

class CAlive : public Component
{
    INC_FACTORY_REGISTER(CAlive);

    int energy;
    int energyMax;
    int health;
    int healthMax;

public:
    virtual bool init(YAML::Node node);

    void updateEnergy(int amount);
    void updateHealth(int amount);
    int getEnergy();
    int getHealth();
};

#endif // CALIVE_H
