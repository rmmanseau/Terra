#ifndef CMOVEMENT_H
#define CMOVEMENT_H

#include "common.h"
#include "component.h"

class CMovement : public Component
{
    Dir direction;
    int velocity;
    int turnAngle;

public:
    virtual bool init(YAML::Node node);

    Dir getUpdatedDirection();
    int getUpdatedVelocity();
};

inline std::shared_ptr<Component> createCMovement()
{
    return std::make_shared<CMovement>();
}

#endif // CMOVEMENT_H
