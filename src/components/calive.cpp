#include "calive.h"

#include <cstdlib>

bool CAlive::init(YAML::Node node)
{
    int healthVar, energyVar;

    try
    {
        health    = node["health"].as<int>();
        healthMax = node["health_max"].as<int>();
        healthVar = node["health_variance"].as<int>();
        energy    = node["energy"].as<int>();
        energyMax = node["energy_max"].as<int>();
        energyVar = node["energy_variance"].as<int>();
    }
    catch(...)
    {
        return false;
    }

    updateHealth((rand() % healthVar*2) - healthVar);
    updateEnergy((rand() % energyVar*2) - energyVar);

    return true;
}

void CAlive::updateEnergy(int amount)
{
    energy += amount;
}
void CAlive::updateHealth(int amount)
{
    health += amount;
}
int CAlive::getEnergy()
{
    return energy;
}
int CAlive::getHealth()
{
    return health;
}
