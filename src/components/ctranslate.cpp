#include "ctranslate.h"

const std::map<Dir, Vec2> CTranslate::dirMap = {
    {Dir::n,  Vec2(0,     -1)},
    {Dir::ne, Vec2(.707,  -.707)},
    {Dir::e,  Vec2(1,      0)},
    {Dir::se, Vec2(.707,   .707)},
    {Dir::s,  Vec2(0,      1)},
    {Dir::sw, Vec2(-.707,  .707)},
    {Dir::w,  Vec2(-1,     0)},
    {Dir::nw, Vec2(-.707, -.707)}
};

bool CTranslate::init(YAML::Node node)
{
    direction = Dir::se;
    velocity = 1;

    return true;
}

void CTranslate::setDirection(Dir d){
    direction = d;
}
void CTranslate::setVelocity(double v){
    velocity = v;
}

Vec2 CTranslate::getDisplacement()
{
    direction = (Dir)(((int)direction+(rand() % 3 - 1) + 8) % 8);
    
    return dirMap.at(direction) * velocity;
}
