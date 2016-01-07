#ifndef CPOSITION_H
#define CPOSITION_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CPosition : public Component
{
    Vec2 pos;

public:
    CPosition()
        : pos(Vec2(0, 0)) {}

    void setPos(Vec2 _pos)
    {
        pos = _pos;
    }
    Vec2 getPos()
    {
        return pos;
    }
};

#endif // CPOSITION_H