#ifndef CPOSITION_H
#define CPOSITION_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CPosition : public Component
{
    INC_FACTORY_REGISTER(CPosition);

public:
    Vec2f pos;

    virtual bool init(YAML::Node node);
};

#endif // CPOSITION_H
