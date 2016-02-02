#ifndef CDUMBBRAIN_H
#define CDUMBBRAIN_H

#include "common.h"
#include "component.h"

class CDumbBrain : public Component
{
    INC_FACTORY_REGISTER(CDumbBrain);

public:
    virtual bool init(YAML::Node node);
};

#endif // CDUMBBRAIN_H
