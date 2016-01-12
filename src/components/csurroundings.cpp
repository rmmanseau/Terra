#include "csurroundings.h"

bool CSurroundings::init(YAML::Node node)
{
    for (int i = 0; i < 8; ++i)
    {
        ids.push_back(0);
        types.push_back(EntityType::Null);
    }

    return true;
}

void CSurroundings::setInfo(int dir, EntityId id, EntityType type)
{
    ids[dir] = id;
    types[dir] = type;
}

int CSurroundings::numberOf(EntityType type)
{
    int amount = 0;
    for (int i = 0; i < types.size(); ++i)
    {
        if (types[i] == type)
            ++amount;
    }
    return amount;
}
