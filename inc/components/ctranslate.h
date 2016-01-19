#ifndef CTRANSLATE_H
#define CTRANSLATE_H

#include "common.h"
#include "component.h"
#include "vec2.h"

#include <cstdlib>
#include <map>

class CTranslate : public Component
{
    INC_FACTORY_REGISTER(CTranslate);

    static const std::map<Dir, Vec2> dirMap;

    Dir direction;
    double velocity;

public:
    virtual bool init(YAML::Node node);

    void setDirection(Dir d);
    void setVelocity(double v);
    Vec2 getDisplacement();
};

#endif // CTRANSLATE_H
