#include "cposition.h"

SRC_FACTORY_REGISTER(CPosition);

bool CPosition::init(YAML::Node node)
{
    try
    {
        pos = Vec2f(node["pos"][0].as<int>(),
                    node["pos"][1].as<int>());
    }
    catch (...)
    {
        return false;
    }
    return true;
}
