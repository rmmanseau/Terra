#include "cposition.h"

bool CPosition::init(YAML::Node node)
{
    pos = Vec2(node["pos"][0].as<int>(),
               node["pos"][1].as<int>());
    return true;
}

void CPosition::setPos(Vec2 _pos)
{
    pos = _pos;
}
Vec2 CPosition::getPos()
{
    return pos;
}