#include "glbl_helpers.h"

void Helpers::init()
{
    directionToVectorMap.insert(std::make_pair(Dir::n , Vec2i( 0, -1)));
    directionToVectorMap.insert(std::make_pair(Dir::ne, Vec2i( 1, -1)));
    directionToVectorMap.insert(std::make_pair(Dir::e , Vec2i( 1,  0)));
    directionToVectorMap.insert(std::make_pair(Dir::se, Vec2i( 1,  1)));
    directionToVectorMap.insert(std::make_pair(Dir::s , Vec2i( 0,  1)));
    directionToVectorMap.insert(std::make_pair(Dir::sw, Vec2i(-1,  1)));
    directionToVectorMap.insert(std::make_pair(Dir::w , Vec2i(-1,  0)));
    directionToVectorMap.insert(std::make_pair(Dir::nw, Vec2i(-1, -1)));
}

Vec2i Helpers::dirToVec(Dir dir)
{
    return directionToVectorMap[dir];
}


Helpers glbl::helpers;
