#include "calive.h"
#include "helpers.h"

#include <cstdlib>

SRC_FACTORY_REGISTER(CAlive);

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

    if (healthVar > 0)
        updateHealth((rand() % healthVar*2) - healthVar);
    if (energyVar > 0)
        updateEnergy((rand() % energyVar*2) - energyVar);

    return true;
}

void CAlive::updateEnergy(int amount)
{
    energy = clamp(energy + amount, 0, energyMax);
}
void CAlive::updateHealth(int amount)
{
    health = clamp(health + amount, 0, healthMax);
}
void CAlive::kill()
{
    health = 0;
}
