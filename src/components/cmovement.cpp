#include "cmovement.h"

bool CMovement::init(YAML::Node node)
{
    direction = Dir::n;
    return true;
}

Vec2 CMovement::getDisplacement()
{
    Vec2 displacement;

    direction = (Dir)(((int)direction+(rand() % 3 - 1) + 8) % 8);

    switch (direction)
    {
        case Dir::n:
            displacement = Vec2(0, -1);
            break;
        case Dir::ne:
            displacement = Vec2(1, -1);
            break;
        case Dir::e:
            displacement = Vec2(1, 0);
            break;
        case Dir::se:
            displacement = Vec2(1, 1);
            break;
        case Dir::s:
            displacement = Vec2(0, 1);
            break;
        case Dir::sw:
            displacement = Vec2(-1, 1);
            break;
        case Dir::w:
            displacement = Vec2(-1, 0);
            break;
        case Dir::nw:
            displacement = Vec2(-1, -1);
            break; 
    }
    return displacement;
}