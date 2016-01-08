#ifndef CPOSITION_H
#define CPOSITION_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CPosition : public Component
{
    Vec2 pos;

public:
    bool init(YAML::Node node);

    void setPos(Vec2 _pos);
    Vec2 getPos();
};

inline std::shared_ptr<Component> createCPosition()
{
    return std::make_shared<CPosition>();
}

#endif // CPOSITION_H