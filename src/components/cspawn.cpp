#include "cspawn.h"

SRC_FACTORY_REGISTER(CSpawn);

bool CSpawn::init(YAML::Node node)
{
    try
    {
        active = false;
        energyCost = node["energy_cost"].as<int>();
        energyRequired = node["energy_required"].as<int>();
        type = (EntityType)node["type"].as<int>();

        pos = Vec2(0, 0);
    }
    catch (...)
    {
        return false;
    }
    return true;
}
