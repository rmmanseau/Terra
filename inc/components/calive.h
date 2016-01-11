#ifndef CALIVE_H
#define CALIVE_H

#include "common.h"
#include "component.h"

class CAlive : public Component
{
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

inline std::shared_ptr<Component> createCAlive()
{
    return std::make_shared<CAlive>();
}

#endif // CALIVE_H