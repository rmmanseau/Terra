#ifndef CMOVEMENT_H
#define CMOVEMENT_H

#include "common.h"
#include "component.h"
#include "vec2.h"

#include <cstdlib>

class CMovement : public Component
{
    Dir direction;

public:
    bool init(YAML::Node node);

    Vec2 getDisplacement();
};

inline std::shared_ptr<Component> createCMovement()
{
    return std::make_shared<CMovement>();
}

#endif // CMOVEMENT_H