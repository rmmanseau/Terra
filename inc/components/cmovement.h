#ifndef CMOVEMENT_H
#define CMOVEMENT_H

#include "common.h"
#include "component.h"

class CMovement : public Component
{
    INC_FACTORY_REGISTER(CMovement);

    Dir direction;
    double velocity;
    int turnAngle;

public:
    virtual bool init(YAML::Node node);

    bool active;

    Dir getUpdatedDirection();
    double getUpdatedVelocity();
};

#endif // CMOVEMENT_H
