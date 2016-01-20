#include "cspawn.h"
#include "globals.h"

SRC_FACTORY_REGISTER(CSpawn);

bool CSpawn::init(YAML::Node node)
{
    try
    {
        active = false;
        energyCost = node["energy_cost"].as<int>();
        energyRequired = node["energy_required"].as<int>();
        type = G_EntityNameTypeMap[node["type"].as<std::string>()];

        for (YAML::const_iterator itr = node["can_spawn_on"].begin();
             itr != node["can_spawn_on"].end(); ++itr)
        {
            canSpawnOn.push_back(G_EntityNameTypeMap[(*itr).as<std::string>()]);
        }

        pos = Vec2i(0, 0);
    }
    catch (...)
    {
        return false;
    }
    return true;
}
