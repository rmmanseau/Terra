#ifndef CPOSITION_H
#define CPOSITION_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CPosition : public Component
{
    INC_FACTORY_REGISTER(CPosition);

    Vec2 pos;

public:
    virtual bool init(YAML::Node node);

    void setPos(Vec2 _pos);
    Vec2 getPos();
};

#endif // CPOSITION_H
