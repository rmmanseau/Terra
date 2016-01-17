#ifndef PROCESS_H
#define PROCESS_H

#include "common.h"

struct Process
{
    virtual void registerEntity(Entity& entity) = 0;
    virtual void unregisterEntity(EntityId id) = 0;
    virtual void update() = 0;
    virtual ~Process() {}
};

#endif // PROCESS_H